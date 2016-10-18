#include "mod_organizer.h"
#include <sstream>

using namespace psjjjj;
using namespace std;

ModOrganizer::ModOrganizer()
    : mod_list_(new ChipModuleListProto) {
}

string ModOrganizer::getModuleList() const {
    return mod_list_->SerializeAsString();
}

string ModOrganizer::generateEntityCodeForModule(string name) const {
    if (mod_id_.count(name) == 0) {
        return string();
    }
    string entity_code = mod_list_->modules(mod_id_.at(name)).entity_code();
    return entity_code;
}

string ModOrganizer::generateComponentCodeForModule(string name) const {
    if (mod_id_.count(name) == 0) {
        return string();
    }
    string port_code = mod_list_->modules(mod_id_.at(name)).entity_code();
    return string("component ") + name + string("\n") +
           port_code + string("end component;\n");
}

int ModOrganizer::load_modules(const string &module_path,
                               const string &module_list_file) {
    string module_list_file_full_path = module_path + string(" ") + module_list_file;
    ifstream module_list_in(module_list_file_full_path);
    if (!module_list_in.is_open()) {
        return 0;
    }
    
    string module_name;
    int module_count = 0;
    while (getline(module_list_in, module_name)) {
        util::trim(module_name);
        if (module_name.empty()) {
            continue;
        }
        
        ifstream module_in(module_name);
        if (!module_in.is_open()) {
            continue;
        }
        
        parse_module(module_name, move(module_in), mod_list_->add_modules());
        ++module_count;
        mod_id_[module_name] = mod_list_->modules_size() - 1;
    }
    
    return module_count;
}

void ModOrganizer::clear_modules() {
    mod_list_.reset(new ChipModuleListProto);
    mod_id_.clear();
}

void ModOrganizer::parse_module(const string &module_name,
                                istream &&module_code,
                                ChipModuleProto *chip_module) {
    enum {
        NONE = 0,
        PORT = 1,
        ENTITY = 2,
        PIN_INFO = 4
    };
    int status = NONE;
    string code_line;
    string port_code;
    string entity_code;
    
    chip_module->set_name(module_name);
    
    while (getline(module_code, code_line)) {
        util::trim(code_line);
        
        // 1. pin info
        
        if (code_line == "--- BEGIN_PIN_INFO ---") {
            status |= PIN_INFO;
        }
        
        if (code_line == "--- END_PIN_INFO ---") {
            status &= ~PIN_INFO;
        }
        
        if (status & PIN_INFO) {
            istringstream line_in(code_line);
            string buf, name, type;
            line_in >> buf >> name >> type;
            ChipModuleProto::Pin *pin = chip_module->add_pins();
            pin->set_name(name);
            pin->set_type(type);
        }
        
        // 2. port code
        
        if (code_line == "--- BEGIN_PORT_DEF ---") {
            status |= PORT;
        }
        
        if (status & PORT) {
            port_code += code_line + string("\n");
        }
        
        if (code_line == "--- END_PORT_DEF ---") {
            status &= ~PORT;
        }
        
        // 3. entity code
        
        if (code_line == "--- BEGIN_CODE ---") {
            status |= ENTITY;
        }
        
        if (status & ENTITY) {
            entity_code += code_line + string("\n");
        }
        
        if (code_line == "--- END_CODE ---") {
            status &= ~ENTITY;
        }
    }
    
    chip_module->set_port_code(port_code);
    chip_module->set_entity_code(entity_code);
}

