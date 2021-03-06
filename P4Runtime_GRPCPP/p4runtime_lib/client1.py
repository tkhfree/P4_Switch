import argparse
import json
import os
import sys

import bmv2
import helper

import time


def error(msg):
    print >> sys.stderr, ' - ERROR! ' + msg

def info(msg):
    print >> sys.stdout, ' - ' + msg

class ConfException(Exception):
    pass

def main():
    parser = argparse.ArgumentParser(description='P4Runtime Simple Controller')

    parser.add_argument('-a', '--p4runtime-server-addr',
                        help='address and port of the switch\'s P4Runtime server (e.g. 192.168.0.1:50051)',
                        type=str, action="store", required=True)
    parser.add_argument('-d', '--device-id',
                        help='Internal device ID to use in P4Runtime messages',
                        type=int, action="store", required=True)
    parser.add_argument('-p', '--proto-dump-file',
                        help='path to file where to dump protobuf messages sent to the switch',
                        type=str, action="store", required=True)
    parser.add_argument("-c", '--runtime-conf-file',
                        help="path to input runtime configuration file (JSON)",
                        type=str, action="store", required=True)

    args = parser.parse_args()

    if not os.path.exists(args.runtime_conf_file):
        parser.error("File %s does not exist!" % args.runtime_conf_file)
    workdir = os.path.dirname(os.path.abspath(args.runtime_conf_file))
    with open(args.runtime_conf_file, 'r') as sw_conf_file:
        program_switch(addr=args.p4runtime_server_addr,
                       device_id=args.device_id,
                       sw_conf_file=sw_conf_file,
                       workdir=workdir,
                       proto_dump_fpath=args.proto_dump_file)

def check_switch_conf(sw_conf, workdir):
    required_keys = ["p4info"]
    files_to_check = ["p4info"]
    target_choices = ["t4p4s"]

    if "target" not in sw_conf:
        raise ConfException("missing key 'target'")
    target = sw_conf['target']
    if target not in target_choices:
        raise ConfException("unknown target '%s'" % target)

    if target == 't4p4s':
        required_keys.append("bmv2_json")
        files_to_check.append("bmv2_json")

    for conf_key in required_keys:
        if conf_key not in sw_conf or len(sw_conf[conf_key]) == 0:
            raise ConfException("missing key '%s' or empty value" % conf_key)

    for conf_key in files_to_check:
        real_path = os.path.join(workdir, sw_conf[conf_key])
        if not os.path.exists(real_path):
            raise ConfException("file does not exist %s" % real_path)

def program_switch(addr, device_id, sw_conf_file, workdir, proto_dump_fpath):
	sw_conf = json_load_byteified(sw_conf_file)
	try:
		check_switch_conf(sw_conf=sw_conf, workdir=workdir)
	except ConfException as e:
		error("While parsing input runtime configuration: %s" % str(e))
		return

	info('Using P4Info file %s...' % sw_conf['p4info'])
	p4info_fpath = os.path.join(workdir, sw_conf['p4info'])
	p4info_helper = helper.P4InfoHelper(p4info_fpath)

	target = sw_conf['target']

	info("Connecting to P4Runtime server on %s (%s)..." % (addr, target))
        

	if target == "t4p4s":
		sw = bmv2.Bmv2SwitchConnection(address=addr, device_id=device_id,
                                       proto_dump_file=proto_dump_fpath)
	else:
		raise Exception("Don't know how to connect to target %s" % target)
               

	try:
            #next(sw.Packet_Out())
	    sw.MasterArbitrationUpdate()
            if target == "t4p4s":
		info("Setting pipeline config (%s)..." % sw_conf['bmv2_json'])
		bmv2_json_fpath = os.path.join(workdir, sw_conf['bmv2_json'])       
		sw.SetForwardingPipelineConfig(p4info=p4info_helper.p4info,
                                           bmv2_json_file_path=bmv2_json_fpath)
 
	    else:
			raise Exception("Should not be here")

	    if 'table_entries' in sw_conf:
		table_entries = sw_conf['table_entries']
		info("Inserting %d table entries..." % len(table_entries))
		for entry in table_entries:
		 	info(tableEntryToString(entry))
			insertTableEntry(sw, entry, p4info_helper)
			# deleteTableEntry(sw,entry,p4info_helper)
			#lookupTableEntry(sw,entry,p4info_helper)
			# pack_in_stream(sw,entry,p4info_helper)

	finally:
		sw.shutdown()


def insertTableEntry(sw, flow, p4info_helper):
    table_name = flow['table']
    match_fields = flow.get('match') # None if not found
    action_name = flow['action_name']
    default_action = flow.get('default_action') # None if not found
    action_params = flow['action_params']
    priority = flow.get('priority')  # None if not found

    table_entry = p4info_helper.buildTableEntry(
        table_name=table_name,
        match_fields=match_fields,
        default_action=default_action,
        action_name=action_name,
        action_params=action_params,
        priority=priority)

    sw.WriteTableEntry(table_entry)

def deleteTableEntry(sw, flow, p4info_helper):
    table_name = flow['table']
    match_fields = flow.get('match') # None if not found
    action_name = flow['action_name']
    default_action = flow.get('default_action') # None if not found
    action_params = flow['action_params']
    priority = flow.get('priority')  # None if not found

    table_entry = p4info_helper.buildTableEntry(
        table_name=table_name,
        match_fields=match_fields,
        default_action=default_action,
        action_name=action_name,
        action_params=action_params,
        priority=priority)

    sw.Write2TableEntry(table_entry)

def lookupTableEntry(sw, flow, p4info_helper):
    print("lockuppppppp")
    table_name = flow['table']
    table_id = p4info_helper.get_tableentry_id(table_name)
    print(table_id)
    dry_run = False
    sw.Read2TableEntries(table_id,dry_run)

def pack_in_stream(sw,flow,p4info_helper):
    print("pack_innnnnn")
    sw.StreamChannelTableEntry()


def json_load_byteified(file_handle):
    return _byteify(json.load(file_handle, object_hook=_byteify),
                    ignore_dicts=True)


def _byteify(data, ignore_dicts=False):
    # if this is a unicode string, return its string representation
    if isinstance(data, unicode):
        return data.encode('utf-8')
    # if this is a list of values, return list of byteified values
    if isinstance(data, list):
        return [_byteify(item, ignore_dicts=True) for item in data]
    # if this is a dictionary, return dictionary of byteified keys and values
    # but only if we haven't already byteified it
    if isinstance(data, dict) and not ignore_dicts:
        return {
            _byteify(key, ignore_dicts=True): _byteify(value, ignore_dicts=True)
            for key, value in data.iteritems()
        }
    # if it's anything else, return it in its original form
    return data


def tableEntryToString(flow):
    if 'match' in flow:
        match_str = ['%s=%s' % (match_name, str(flow['match'][match_name])) for match_name in
                     flow['match']]
        match_str = ', '.join(match_str)
    elif 'default_action' in flow and flow['default_action']:
        match_str = '(default action)'
    else:
        match_str = '(any)'
    params = ['%s=%s' % (param_name, str(flow['action_params'][param_name])) for param_name in
              flow['action_params']]
    params = ', '.join(params)
    return "%s: %s => %s(%s)" % (
        flow['table'], match_str, flow['action_name'], params)

if __name__ == '__main__':
	main()
