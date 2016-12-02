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
    vector<string> module_set = mod_organizer_->getAllModuleName();
    map<string, util::ChipStatus> chips;
    map<string, string> input_set;
    map<string, string> output_set;
    map<string, CircuitProto::Chip::Activation> activation;
    for (int i = 0; i < circuit.chips_size(); ++i) {
        string type = circuit.chips(i).type();
        string name = circuit.chips(i).id();
        if (type == "input") {
            string input_name = string("input_") + to_string(input_set.size() + 1);
            input_set.insert(make_pair(name, input_name));
            if (circuit.chips(i).has_activation()) {
                activation.insert(make_pair(name, circuit.chips(i).activation()));
            }
        }
        else if (type == "output") {
            string output_name = string("output_") + to_string(output_set.size() + 1);
            output_set.insert(make_pair(name, output_name));
        }
        else {
            chips[name] = {type, map<string, string>()};
        }
    }
    
    // 1.2 parse wires
    vector<string> wire_list;
    map<string, vector<string>> input_map;
    map<string, vector<string>> wire_map; //wires which are connected to a same pin
    map<string, string> output_map;
    for (int i = 0; i < circuit.wires_size(); ++i) {
        CircuitProto::Wire wire = circuit.wires(i);
        string wire_name = string("wire_") + to_string(i + 1);
        wire_list.push_back(wire_name);
        
        for (CircuitProto::Wire::Pin pin : {wire.start_pin(), wire.end_pin()}) {
            if (input_set.count(pin.chip_name())) {
                string input_name = input_set.at(pin.chip_name());
                input_map[input_name].push_back(wire_name);
            }
            else if (output_set.count(pin.chip_name())) {
                string output_name = output_set.at(pin.chip_name());
                output_map[output_name] = wire_name;
            }
            else {
                if (chips.count(pin.chip_name()) == 0) {
                    continue;
                }
                if (chips[pin.chip_name()].pin.count(pin.pin_name()) == 0)
                    chips[pin.chip_name()].pin[pin.pin_name()] = wire_name;
                else {
                    string main_wire = chips[pin.chip_name()].pin[pin.pin_name()];
                    wire_map[main_wire].push_back(wire_name);
                }
            }
        }
    }
    
    // 2. generating
    // 2.1 generate modules' entity
    for (const string &name : module_set) {
        code += mod_organizer_->generateEntityCodeForModule(name) + "\n";
    }

    // 2.2 generate main entity
    code += "LIBRARY IEEE;\n";
    code += "USE IEEE.STD_LOGIC_1164.ALL;\n";
    code += "USE IEEE.STD_LOGIC_ARITH.ALL;\n";
    code += "USE IEEE.STD_LOGIC_UNSIGNED.ALL;\n\n";
    
    code += "entity main is\n";
    code += "port(\n";
    string ending = "";
    for (const auto &output : output_map) {
        code += ending + "    " + output.first + ": out std_logic";
        ending = ";\n";
    }
    code += "\n);\nend main;\n";
    
    // 2.3 generate main struct
    const vector<string> std_logic = {"'0'", "'1'"};
    code += "architecture struct of main is\n\n";
    for (const string &name : module_set) {
        code += mod_organizer_->generateComponentCodeForModule(name) + "\n";
    }
    for (const auto &input : input_map) {
        code += string("signal ") + input.first + ": std_logic := ";
        if (activation.count(input.first)) {
            code += std_logic[activation.at(input.first).initial()] + ";\n";
        }
        else {
            code += "'1';\n";
        }
    }
    for (const string &name : wire_list) {
        code += string("signal ") + name + ": std_logic;\n";
    }
    code += "\nbegin\n\n";
    for (const auto &input : input_set) {
        if (activation.count(input.first)) {
            auto act = activation.at(input.first);
            int current_time = 0;
            bool initial = act.initial();
            code += "process\n";
            code += "begin\n";
            for (int i = 0; i < act.jumping_time_size(); ++i) {
                initial = !initial;
                code += "    wait for ";
                code += to_string(act.jumping_time(i) - current_time) + "ps;\n";
                code += "    " + input.second + " <= " + std_logic[initial] + ";\n";
                current_time = act.jumping_time(i);
            }
            if (!act.repeat()) {
                code += "    wait;\n";
            }
            code += "end process;\n\n";
        }
    }
    for (const auto &input : input_map) {
        for (const auto &wire : input.second) {
            code += wire + " <= " + input.first + ";\n";
        }
    }
    for (const auto &output : output_map) {
        code += output.first + " <= " + output.second + ";\n";
    }
    for (const auto &wire : wire_map) {
        for (const auto &wire2 : wire.second) {
            code += wire2 + " <= " + wire.first + ";\n";
        }
    }
    for (const auto &chip : chips) {
        code += "u_";
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
    int pin_id = 0;
    for (auto &pin : pin_list) {
        if (pin.type() != "in" && pin.type() != "out") {
            ++pin_id;
            continue;
        }
        if (starting) {
            starting = false;
        }
        else {
            code += ", ";
        }
        string mapping;
        string pin_id_str = std::to_string(pin_id);
        if (status.pin.count(pin_id_str)) {
            mapping = status.pin.at(pin_id_str);
        }
        else if (pin.type() == "in") {
            mapping = "'1'";
        }
        else {
            mapping = "open";
        }
        code += pin.name() + "=>" + mapping;
        ++pin_id;
    }
    code += ");";
    return code;
}

