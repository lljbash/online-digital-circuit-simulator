#include "engine_handler.h"
#include "util/util.h"
#include "vhdl_parsing_result.pb.h"
#include "simulation_result.pb.h"

using namespace psjjjj;
using namespace std;

EnginePtr Engine::createEngine(string out_path) {
    return EnginePtr(new EngineHandler(out_path));
}

EngineHandler::EngineHandler(string out_path) :
    mod_organizer_(new ModOrganizer()),
    vhdl_parser_(new VHDLParser()),
    simulator_(new Simulator()),
    out_path_(out_path) {
}

string EngineHandler::getChipModuleList() const {
    return mod_organizer_->getModuleList();
}

string EngineHandler::getVHDLParsingResult() const {
    VHDLParsingResultProto vprp = vhdl_parser_->parse();
    return vprp.SerializeAsString();
}

string EngineHandler::getSimulationResult(string vhdl_source_code) const {
    SimulationResultProto srp = simulator_->simulate(vhdl_source_code, out_path_);
    return srp.SerializeAsString();
}

int EngineHandler::addChipModules(string path, string file) {
    return mod_organizer_->load_modules(path, file);
}

