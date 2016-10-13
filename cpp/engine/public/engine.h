#pragma once

#include <string>
#include <memory>

namespace psjjjj {

using EnginePtr = std::unique_ptr<class Engine>;

class Engine {

    public:
        Engine() = default;
        
        virtual std::string getVHDLParsingResult() const = 0;
        virtual std::string getSimulationResult(std::string vhdl_source_code) const = 0;
        
        static EnginePtr createEngine(std::string out_path);
         
        Engine(const Engine &) = delete;
        void operator=(const Engine &) = delete;
        
};

} // namespace psjjjj

