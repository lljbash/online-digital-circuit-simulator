#include "circuit_parser.h"
#include <unistd.h>

using namespace psjjjj;
using namespace std;

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

