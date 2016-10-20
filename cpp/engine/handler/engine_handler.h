#pragma once

#include "engine.h"
#include "module/mod_organizer/mod_organizer.h"
#include "module/circuit_parser/circuit_parser.h"
#include "module/simulator/simulator.h"

namespace psjjjj {
    
class EngineHandler : public Engine {

    public:
        EngineHandler(std::string out_path);
        
        virtual std::string getChipModuleList() const override;
        virtual std::string getCircuitParsingResult() const override;
        virtual std::string getSimulationResult(std::string vhdl_source_code) const override;
        
        virtual int addChipModules(std::string path, std::string file) override;
        
    private:
        std::shared_ptr<ModOrganizer> mod_organizer_;
        std::unique_ptr<CircuitParser> circuit_parser_;
        std::unique_ptr<Simulator> simulator_;
        std::string out_path_;
    
};

} // namespace psjjjj

