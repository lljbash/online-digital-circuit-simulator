#include "vhdl_parser.h"

using namespace psjjjj;
using namespace std;

VHDLParsingResultProto VHDLParser::parse() {
    PSJJJJ_SHOW("parsing...");
    PSJJJJ_SHOW("parsing done!");
    
    VHDLParsingResultProto vprp;
    vprp.set_success(true);
    vprp.set_vhdl_code("hello world");
    
    return vprp;
}

