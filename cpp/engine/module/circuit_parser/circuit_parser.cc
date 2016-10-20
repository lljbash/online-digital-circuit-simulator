#include "circuit_parser.h"
#include <unistd.h>

using namespace psjjjj;
using namespace std;

CircuitParser::CircuitParser(shared_ptr<const ModOrganizer> mod_organizer) {
    mod_organizer_ = move(mod_organizer);
}

CircuitParsingResultProto CircuitParser::parse() {
    PSJJJJ_SHOW("parsing...\n");
    usleep(5000000);
    PSJJJJ_SHOW("parsing done!\n");
    
    CircuitParsingResultProto vprp;
    vprp.set_success(true);
    FILE *vhdl_file = fopen("data/test/engine/simulator/test.vhd", "r");
    char code[999];
    fread(code, sizeof(char), 999, vhdl_file);
    fclose(vhdl_file);
    vprp.set_vhdl_code(code);
    
    return vprp;
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
        if (pin.name() == "input") {
            mapping = "'1'";
        }
        else if (pin.name() == "output") {
            mapping = "output";
        }
        else if (status.pin.count(pin.name())) {
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

