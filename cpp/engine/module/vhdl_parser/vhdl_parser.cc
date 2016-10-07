#include "vhdl_parser.h"
#include <unistd.h>

using namespace psjjjj;
using namespace std;

VHDLParsingResultProto VHDLParser::parse() {
    PSJJJJ_SHOW("parsing...\n");
    usleep(5000000);
    PSJJJJ_SHOW("parsing done!\n");
    
    VHDLParsingResultProto vprp;
    vprp.set_success(true);
    vprp.set_vhdl_code("hello world");
    
    return vprp;
}

