#pragma once

#include "engine.h"
#include "module/mod_organizer/mod_organizer.h"
#include "module/vhdl_parser/vhdl_parser.h"
#include "module/simulator/simulator.h"

namespace psjjjj {
    
class EngineHandler : public Engine {

    public:
        EngineHandler(std::string out_path);
        
        virtual std::string getChipModuleList() const override;
        virtual std::string getVHDLParsingResult() const override;
        virtual std::string getSimulationResult(std::string vhdl_source_code) const override;
        
        virtual int addChipModules(std::string path, std::string file) override;
        
    private:
        std::unique_ptr<ModOrganizer> mod_organizer_;
        std::unique_ptr<VHDLParser> vhdl_parser_;
        std::unique_ptr<Simulator> simulator_;
        std::string out_path_;
    
};

} // namespace psjjjj

