#include "simulator.h"

using namespace psjjjj;
using namespace std;

SimulationResultProto Simulator::simulate(string vhdl_source_code) {
    PSJJJJ_SHOW("start simulating...");
    //TODO: execute modelsim to simulate
    PSJJJJ_SHOW("end simulating.");
    
    SimulationResultProto srp;
    srp.set_success(true);
    srp.set_file_name("example.txt");
    return srp;
}

