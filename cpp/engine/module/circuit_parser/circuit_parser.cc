#include "circuit_parser.h"
#include <unistd.h>

using namespace psjjjj;
using namespace std;

CircuitParser::CircuitParser(shared_ptr<const ModOrganizer> mod_organizer) {
    mod_organizer_ = move(mod_organizer);
}

CircuitParsingResultProto CircuitParser::parse(const CircuitProto &circuit) {
    CircuitParsingResultProto result;
    string code;
    
    PSJJJJ_SHOW("parsing...\n");
    
    // 1. parsing
    // 1.1 parse chips
    set<string> module_set;
    map<string, util::ChipStatus> chips;
    for (int i = 0; i < circuit.chips_size(); ++i) {
        module_set.insert(circuit.chips(i).type());
        chips[circuit.chips(i).id()] = {circuit.chips(i).type(), map<string, string>()};
    }
    
    // 1.2 parse wires
    vector<string> wire_list;
    map<string, string> input_map;
    map<string, string> output_map;
    for (int i = 0; i < circuit.wires_size(); ++i) {
        CircuitProto::Wire wire = circuit.wires(i);
        string wire_name = string("wire_") + to_string(i + 1);
        
        for (CircuitProto::Wire::Pin pin : {wire.start_pin(), wire.end_pin()}) {
            if (pin.chip_name() == "input") {
                string input_name = string("input_") + to_string(input_map.size() + 1);
                input_map[input_name] = wire_name;
            }
            else if (pin.chip_name() == "output") {
                string output_name = string("output_") + to_string(output_map.size() + 1);
                output_map[output_name] = wire_name;
            }
            else {
                if (chips.count(pin.chip_name()) == 0) {
                    continue;
                }
                chips[pin.chip_name()].pin[pin.pin_name()] = wire_name;
            }
        }
    }
    
    // 2. generating
    // 2.1 generate headers
    code += "LIBRARY IEEE;\n";
    code += "USE IEEE.STD_LOGIC_1164.ALL;\n";
    code += "USE IEEE.STD_LOGIC_ARITH.ALL;\n";
    code += "USE IEEE.STD_LOGIC_UNSIGNED.ALL;\n\n";
    
    // 2.2 generate modules' entity
    for (const string &name : module_set) {
        code += mod_organizer_->generateEntityCodeForModule(name) + "\n";
    }

    // 2.3 generate main entity
    code += "entity main is\n";
    code += "port(\n";
    string ending = "";
    for (const auto &input : input_map) {
        code += ending + "    " + input.first + ": in std_logic";
        ending = ";\n";
    }
    for (const auto &output : output_map) {
        code += ending + "    " + output.first + ": out std_logic";
        ending = ";\n";
    }
    code += "\n);\nend main;\n";
    
    // 2.4 generate main struct
    code += "architecture struct of main is\n\n";
    for (const string &name : module_set) {
        code += mod_organizer_->generateComponentCodeForModule(name) + "\n";
    }
    for (const string &name : wire_list) {
        code += string("signal ") + name + ": std_logic;\n";
    }
    code += "\nbegin\n\n";
    for (const auto &chip : chips) {
        code += "    u_";
        code += chip.first;
        code += ": ";
        code += generatePinMapping(chip.second);
        code += "\n";
    }
    code += "\nend struct;\n";
    
    PSJJJJ_SHOW("parsing done!\n");
    
    result.set_success(true);
    result.set_vhdl_code(code);
    
    return result;
}

string CircuitParser::generatePinMapping(const util::ChipStatus &status) const {
    vector<ChipModuleProto::Pin> pin_list = mod_organizer_->getPinList(status.type);
    string code = status.type + " port map (";
    bool starting = true;
    for (auto &pin : pin_list) {
        if (pin.type() != "in" && pin.type() != "out") {
            continue;
        }
        if (starting) {
            starting = false;
        }
        else {
            code += ", ";
        }
        string mapping;
        if (status.pin.count(pin.name())) {
            mapping = status.pin.at(pin.name());
        }
        else {
            mapping = "open";
        }
        code += pin.name() + "=>" + mapping;
    }
    code += ");";
    return code;
}

