#include "device_mgr.h"
#include "google/rpc/code.pb.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <arpa/inet.h>


struct ConfigFile {
 public:
  ConfigFile() { }

  ~ConfigFile() {
    if (fp != nullptr) std::fclose(fp);
  }

  grpc::Status change_config(const ::p4::v1::ForwardingPipelineConfig &config_proto) {
    if (fp != nullptr) std::fclose(fp);  // delete old file
    fp = std::tmpfile();  // new temporary file
    if (!fp) {
	    return grpc::Status::OK; //TODO
    }
    if (config_proto.p4_device_config().size() > 0) {
      auto nb_written = std::fwrite(config_proto.p4_device_config().data(),
                                    config_proto.p4_device_config().size(),
                                    1,
                                    fp);
      /*if (nb_written != 1) {
        RETURN_ERROR_STATUS(
            Code::INTERNAL, "Error when saving config to temporary file");
      }*/
    }
    size = config_proto.p4_device_config().size();
    return grpc::Status::OK;
  }

  grpc::Status read_config(::p4::v1::ForwardingPipelineConfig *config_proto) {
    if (!fp || size == 0) return grpc::Status::OK;  // no config was saved
    if (std::fseek(fp, 0, SEEK_SET) != 0) {  // seek to start
	    return grpc::Status::OK; // TODO
      /*RETURN_ERROR_STATUS(
          Code::INTERNAL,
          "Error when reading saved config from temporary file");*/
    }
    // Unfortunately, in C++11, one cannot write directly to the std::string
    // storage (unlike in C++17), so we need an extra copy. To avoid having 2
    // copies of the config simultaneously in memory, we read the file by chunks
    // of 512 bytes.
    char buffer[512];
    auto *device_config = config_proto->mutable_p4_device_config();
    device_config->reserve(size);
    size_t iters = size / sizeof(buffer);
    size_t remainder = size - iters * sizeof(buffer);
    size_t i;
    for (i = 0; i < iters && std::fread(buffer, sizeof(buffer), 1, fp); i++) {
      device_config->append(buffer, sizeof(buffer));
    }
    if (i != iters ||
        (remainder != 0 && !std::fread(buffer, remainder, 1, fp))) {
	    return grpc::Status::OK;
      /*RETURN_ERROR_STATUS(
          Code::INTERNAL,
          "Error when reading saved config from temporary file");*/
    }
    device_config->append(buffer, remainder);
    return grpc::Status::OK;
  }

 private:
  std::FILE *fp{nullptr};
  size_t size{0};
};

ConfigFile saved_device_config;
bool has_config_cookie{false};
::p4::v1::ForwardingPipelineConfig::Cookie config_cookie;

struct p4_field_match_header* _gen_match_rule_exact(argument_t *arg, const ::p4::v1::FieldMatch::Exact &exact) {
	struct p4_field_match_exact *result = malloc(sizeof(struct p4_field_match_exact));

	strcpy(result->header.name, arg->name);
	result->header.type = P4_FMT_EXACT;
	result->length = arg->bitwidth;
	memcpy(result->bitmap, exact.value().c_str(), exact.value().size());

	return (struct p4_field_match_header*)result; /* TODO: NTOH !!! */
}

struct p4_field_match_header* _gen_match_rule_lpm(argument_t *arg, const ::p4::v1::FieldMatch::LPM &lpm) {
        struct p4_field_match_lpm *result = malloc(sizeof(struct p4_field_match_lpm));

        strcpy(result->header.name, arg->name);
        result->header.type = P4_FMT_LPM;
        result->prefix_length = lpm.prefix_len();
        memcpy(result->bitmap, lpm.value().c_str(), lpm.value().size());

        return (struct p4_field_match_header*)result; /* TODO: NTOH !!! */
}

struct p4_field_match_header* _gen_match_rule_ternary(argument_t *arg, const ::p4::v1::FieldMatch::Ternary &ternary) {
        struct p4_field_match_ternary *result = malloc(sizeof(struct p4_field_match_ternary));

        strcpy(result->header.name, arg->name);
        result->header.type = P4_FMT_TERNARY;
        result->length = arg->bitwidth;
        memcpy(result->bitmap, ternary.value().c_str(), ternary.value().size());
	memcpy(result->mask, ternary.mask().c_str(), ternary.mask().size());

        return (struct p4_field_match_header*)result; /* TODO: NTOH !!! */
}

struct p4_action_parameter* _gen_action_param(argument_t *arg, const ::p4::v1::Action::Param &param) {
	struct p4_action_parameter *result = malloc(sizeof(struct p4_action_parameter));
	uint16_t *tmp16;
	uint32_t *tmp32;

	strcpy(result->name, arg->name);
	result->length = arg->bitwidth;
	memcpy(result->bitmap, param.value().c_str(), param.value().size());
	if (param.value().size()==2) {
		tmp16 = (uint16_t*)result->bitmap;
		*tmp16 = htons(*tmp16);
	} else if (param.value().size()==4) {
		tmp32 = (uint32_t*)result->bitmap;
		*tmp32 = htonl(*tmp32);
        }

	return result; /* TODO: NTOH  */
}

grpc::Status table_insert(device_mgr_t *dm, const ::p4::v1::TableEntry &table_entry) {
	uint32_t table_id;
	uint32_t field_id;
	uint32_t action_id;
	uint16_t value16; /* TODO: remove after testing */
	uint8_t ip[4]; /* TODO: remove after testing */
	size_t i;
	int32_t prefix_len = 0; /* in bits */

	grpc::Status status = grpc::Status::OK;
	std::cout << "table-insert --------\n";
//	::p4::v1::FieldMatch match;
//	::p4::v1::TableAction action;
//	::p4::v1::FieldMatch::Exact exact;
//	::p4::v1::FieldMatch::LPM lpm;
//	::p4::v1::FieldMatch::Ternary ternary;
	
//	::p4::v1::Action tmp_act;
//	::p4::v1::Action::Param param;
	
	table_id = table_entry.table_id();

	element_t *elem = get_element(&(dm->id_map), table_id);
	std::cout<<"elem_value:"<<elem->value;
	argument_t *arg = NULL;

	struct p4_ctrl_msg ctrl_m;
	ctrl_m.num_field_matches = 0;
	ctrl_m.num_action_params = 0;
	ctrl_m.type = P4T_ADD_TABLE_ENTRY;
	ctrl_m.table_name = strdup(elem->value);
	std::cout<<"table_name:"<<ctrl_m.table_name;

	for (const auto &match: table_entry.match()) {
		field_id = match.field_id();
		arg = get_argument(elem, field_id);
		std::cout<<"range match 1111111111";
		if (arg==NULL) {
			printf("NULL ARGUMENT for FIELD_ID=%d\n", field_id);
		}
		switch(match.field_match_type_case()) {
			case ::p4::v1::FieldMatch::FieldMatchTypeCase::kExact:
				std::cout<<"field_match_exact22222222";
				const auto exact = match.exact();
				ctrl_m.field_matches[ctrl_m.num_field_matches] = _gen_match_rule_exact(arg, exact);
				ctrl_m.num_field_matches++;	
				//status.set_code(Code::OK);
				break;
			case ::p4::v1::FieldMatch::FieldMatchTypeCase::kLpm:
				std::cout<<"field_match_lpmmmmm3333333";
				const auto lpm = match.lpm();
				prefix_len = lpm.prefix_len();
                                if (lpm.value().size()>=4) {
					ip[0] = lpm.value().c_str()[0];
					ip[1] = lpm.value().c_str()[1];
					ip[2] = lpm.value().c_str()[2];
					ip[3] = lpm.value().c_str()[3];
				}
				printf("LPM MATCH TableID:%:%d (%s) FieldID:%d (%s) KEY_LENGTH:%d VALUE_IP: %d.%d.%d.%d PREFIX_LEN: %d  -- \n", table_id, elem->value, field_id, arg->name, lpm.value().size(), (int)ip[0], (int)ip[1], (int)ip[2], (int)ip[3],  prefix_len);
				ctrl_m.field_matches[ctrl_m.num_field_matches] = _gen_match_rule_lpm(arg, lpm);
				ctrl_m.num_field_matches++;
				status = grpc::Status::OK;
				break;
			case ::p4::v1::FieldMatch::FieldMatchTypeCase::kTernary:
				std::cout<<"field_match_ternary444444";
				const auto ternary = match.ternary();
				printf("TERNARY MATCH TableID:%d (%s) FieldID:%d (%s) KEY_LENGTH:%d VALUE16: %d M_LEN:%d MASK:%d  --\n", table_id, elem->value, field_id, arg->name, ternary.value().size(), ternary.value().c_str()[0], ternary.mask().size(), ternary.mask().c_str()[0]); /* len - length , data - uint8_t* */
				ctrl_m.field_matches[ctrl_m.num_field_matches] = _gen_match_rule_ternary(arg, ternary);
				ctrl_m.num_field_matches++;
                                //status.gcs_code = GOOGLE__RPC__CODE__OK;
                                break;

			case ::p4::v1::FieldMatch::FieldMatchTypeCase::kRange:	
			default:
				std::cout<<"field_match_range555555";
				status = grpc::Status( grpc::StatusCode::UNIMPLEMENTED, "MatchType is not implemented" );
				break;
		}
	}
//return status; } //
	if (table_entry.is_default_action()) { /* n_match is 0 in this case */
		ctrl_m.type = P4T_SET_DEFAULT_ACTION;
	}

	const auto action = table_entry.action();

	switch(action.type_case()) {
		case ::p4::v1::TableAction::TypeCase::kAction:
			std::cout<<"field_match_action666666";
			ctrl_m.action_type = P4_AT_ACTION; /* ACTION PROFILE IS NOT SUPPORTED */
			const auto tmp_act = action.action();
			action_id = tmp_act.action_id();
			elem = get_element(&(dm->id_map), action_id);
			ctrl_m.action_name = strdup(elem->value);
			for (const auto &param: tmp_act.params()) {
				//param = tmp_act->params[i];
				std::cout<<"field_match_7777777";
				arg = get_argument(elem, param.param_id());
				ctrl_m.action_params[ctrl_m.num_action_params] = _gen_action_param(arg, param);
				ctrl_m.num_action_params++;
			}
			//status.gcs_code = GOOGLE__RPC__CODE__OK;
			break;
		default:
			status = grpc::Status( grpc::StatusCode::UNIMPLEMENTED, "ActionType is not implemented" );
			break;
	}

	if (status.ok()) {
		std::cout<<"return status8888888";
		dm->cb(&ctrl_m);
	}

        return status;
}

grpc::Status table_modify(device_mgr_t *dm, const ::p4::v1::TableEntry &table_entry) {
	grpc::Status status;
	status = grpc::Status( grpc::StatusCode::UNIMPLEMENTED, "table_modify is not implemented" );
	return status;
}

grpc::Status table_delete(device_mgr_t *dm, const ::p4::v1::TableEntry &table_entry) {
	grpc::Status status;
	std::cout<<"table_deleteeeeeeeeeeeeeeeeeee";
	status = grpc::Status( grpc::StatusCode::UNIMPLEMENTED, "table_delete is not implemented" );
        return status;
	
}

bool check_p4_id(uint32_t id, int type) {
	return true;
}

grpc::Status table_write(device_mgr_t *dm, ::p4::v1::Update::Type update, const ::p4::v1::TableEntry &table_entry) {
	grpc::Status status;
	std::cout << "table_write ************";
	if (!check_p4_id(table_entry.table_id(), P4IDS_TABLE)) {
		status = grpc::Status( grpc::StatusCode::UNKNOWN, "P4ID is not unknown" );
		return status; /*TODO: more informative error msg is needed!!!*/
	}

	switch (update) {
		case ::p4::v1::Update::UNSPECIFIED:
			status = grpc::Status( grpc::StatusCode::INVALID_ARGUMENT, "Invalid argument" );
			/*TODO: more informative error msg is needed!!!*/
	        	break;
		case ::p4::v1::Update::INSERT:
			return table_insert(dm, table_entry);
		case ::p4::v1::Update::MODIFY:
			return table_modify(dm, table_entry);
		case ::p4::v1::Update::DELETE:
			return table_delete(dm, table_entry);
		default:
			status = grpc::Status( grpc::StatusCode::UNKNOWN, "Unknown update message" );
			/*TODO: more informative error msg is needed!!!*/
			break;
	}
	return status;
}

// Copied from p4lang/PI
class P4ErrorReporter {
 public:
  void push_back(const ::p4::v1::Error &error) {
    //if (!error.canonical_code().ok())
    //  errors.emplace_back(index, error);
    //index++;
  }

  // TODO(antonin): remove this overload when we generalize the use of
  // p4v1::Error in the code?
  void push_back(const grpc::Status &status) {
    //if (!status.ok()) {
    //  ::p4::v1::Error error;
      //error.set_canonical_code(status.error_code());
      //error.set_message(status.message());
      //error.set_space("ALL-sswitch-p4org");
      //errors.emplace_back(index, error);
    //}
    //index++;
  }

  grpc::Status get_status() const {
    grpc::Status status;
    if (errors.empty()) {
      status = grpc::Status::OK;
    } else {
      status = grpc::Status(grpc::StatusCode::UNKNOWN, "Unknown");
/*      ::p4::v1::Error success;
      success.set_code(Code::OK);
      status.set_code(Code::UNKNOWN);
      size_t i = 0;
      for (const auto &p : errors) {
        for (; i++ < p.first;) {
          auto success_any = status.add_details();
          success_any->PackFrom(success);
        }
        auto error_any = status.add_details();
        error_any->PackFrom(p.second);
      }
      // add trailing OKs
      for (; i++ < index;) {
        auto success_any = status.add_details();
        success_any->PackFrom(success);
      }*/
    }
    return status;
  }

 private:
  std::vector<std::pair<size_t, ::p4::v1::Error> > errors{};
  size_t index{0};
};


grpc::Status dev_mgr_write(device_mgr_t *dm, const ::p4::v1::WriteRequest &request, ::p4::v1::WriteResponse *response) {
	grpc::Status status = grpc::Status::OK;
	size_t i;
	std::cout<<"dev_mgr_write*******";
	if (request.atomicity() != ::p4::v1::WriteRequest::CONTINUE_ON_ERROR) {
		status = grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "Not implemented");
		return status;
	}

	P4ErrorReporter error_reporter;

	for (const auto &update : request.updates()) {
		const auto entity = update.entity();
		switch(entity.entity_case()) {
			case ::p4::v1::Entity::kTableEntry:
				std::cout<<"case-----";
				status = table_write(dm, update.type(), entity.table_entry());
				break;
			default:
				status = grpc::Status(grpc::StatusCode::UNKNOWN, "Entity case is unknown");
				break;
		}
		/* TODO:collect multiple status messages - now we assume a simple update */
		error_reporter.push_back(status);
	}
	
	return error_reporter.get_status();
}

grpc::Status dev_mgr_read(device_mgr_t *dm, const ::p4::v1::ReadRequest &request, ::p4::v1::ReadResponse *response) {
	return grpc::Status::OK;
}

grpc::Status dev_mgr_set_pipeline_config(device_mgr_t *dm, ::p4::v1::SetForwardingPipelineConfigRequest_Action action, const ::p4::v1::ForwardingPipelineConfig config) {
	using SetConfigRequest = ::p4::v1::SetForwardingPipelineConfigRequest;
	grpc::Status status(grpc::StatusCode::OK, "ok");

	if (action == SetConfigRequest::VERIFY ||
        action == SetConfigRequest::VERIFY_AND_SAVE ||
        action == SetConfigRequest::VERIFY_AND_COMMIT ||
        action == SetConfigRequest::RECONCILE_AND_COMMIT) {
		printf("P4Info configuration received...\n");
		dm->p4info.CopyFrom( config.p4info() );
		dm->has_p4info = 1;
		config_cookie.CopyFrom(config.cookie());
		saved_device_config.change_config(config); // TODO: return value
		has_config_cookie = true;
		element_t *elem;
		size_t i,j;
		for (const auto &table : dm->p4info.tables()) {
			const auto &pre = table.preamble();
			printf("  [+] TABLE id: %d; name: %s\n", pre.id(), pre.name().c_str());
			elem = add_element(&(dm->id_map), pre.id(), pre.name().c_str());
	                if (elem == NULL) {
        	                printf("   +-----> ERROR\n");
                	        break;
                	}
			for (const auto &mf : table.match_fields()) {
				printf("   +-----> MATCH FIELD; name: %s; id: %d; bitwidth: %d\n", mf.name().c_str(), mf.id(), mf.bitwidth());
				strcpy(elem->args[elem->n_args].name, mf.name().c_str());
	                        elem->args[elem->n_args].id = mf.id();
        	                elem->args[elem->n_args].bitwidth = mf.bitwidth();
                	        elem->n_args++;
			}

                }
		for (const auto &taction : dm->p4info.actions()) {
			const auto &pre = taction.preamble();
			printf("  [#] ACTION id: %d; name: %s\n", pre.id(), pre.name().c_str());
                	elem = add_element(&(dm->id_map), pre.id(), pre.name().c_str());
                	for (const auto &param : taction.params()) {
                        	printf("   #-----> ACTION PARAM; name: %s; id: %d; bitwidth: %d\n", param.name().c_str(), param.id(), param.bitwidth());
                        	strcpy(elem->args[elem->n_args].name, param.name().c_str());
                        	elem->args[elem->n_args].id = param.id();
	                        elem->args[elem->n_args].bitwidth = param.bitwidth();
        	                elem->n_args++;
                	}
		}

		return status;
	}

	return status; // TODO
}

grpc::Status dev_mgr_get_pipeline_config(device_mgr_t *dm, ::p4::v1::GetForwardingPipelineConfigRequest::ResponseType response_type, ::p4::v1::ForwardingPipelineConfig *config) {
	using GetConfigRequest = ::p4::v1::GetForwardingPipelineConfigRequest;
	switch (response_type) {
      		case GetConfigRequest::ALL:
        		config->mutable_p4info()->CopyFrom(dm->p4info);
        		saved_device_config.read_config(config);
        		break;
      		case GetConfigRequest::COOKIE_ONLY:
        		break;
      		case GetConfigRequest::P4INFO_AND_COOKIE:
        		config->mutable_p4info()->CopyFrom(dm->p4info);
        		break;
      		case GetConfigRequest::DEVICE_CONFIG_AND_COOKIE:
        		saved_device_config.read_config(config);
        		break;
      		default:
			return grpc::Status::OK;
    	}
	if (has_config_cookie)
      		config->mutable_cookie()->CopyFrom(config_cookie);
	return grpc::Status::OK;
}

void dev_mgr_init(device_mgr_t *dm) {
	init_map(&(dm->id_map));
	dm->has_p4info = 0;
}

void dev_mgr_init_with_t4p4s(device_mgr_t *dm, p4_msg_callback cb, uint64_t device_id) {
	dev_mgr_init(dm);
	dm->cb = cb;
	dm->device_id = device_id;
}
