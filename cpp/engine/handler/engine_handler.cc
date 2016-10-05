#include "engine_handler.h"
#include "util/util.h"
#include "vhdl_parsing_result.pb.h"
#include "simulation_result.pb.h"

using namespace psjjjj;
using namespace std;

EnginePtr Engine::createEngine() {
    return EnginePtr(new EngineHandler());
}

EngineHandler::EngineHandler() :
    vhdl_parser_(new VHDLParser()),
    simulator_(new Simulator()) {
}

string EngineHandler::getVHDLParsingResult() const {
    VHDLParsingResultProto vprp = vhdl_parser_->parse();
    return vprp.SerializeAsString();
}

string EngineHandler::getSimulationResult(string vhdl_source_code) const {
    SimulationResultProto srp = simulator_->simulate(vhdl_source_code);
    return srp.SerializeAsString();
}

