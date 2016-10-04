#pragma once

#include "engine.h"
#include "module/vhdl_parser/vhdl_parser.h"
#include "module/simulator/simulator.h"

namespace psjjjj {
    
class EngineHandler : public Engine {

    public:
        EngineHandler();
        
        virtual std::string getVHDLParsingResult() const override;
        virtual std::string getSimulationResult(std::string vhdl_source_code) const override;
        
    private:
        std::unique_ptr<VHDLParser> vhdl_parser_;
        std::unique_ptr<Simulator> simulator_;
    
};

} // namespace psjjjj

