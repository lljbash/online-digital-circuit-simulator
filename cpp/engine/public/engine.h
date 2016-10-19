#pragma once

#include <string>
#include <memory>

namespace psjjjj {

using EnginePtr = std::unique_ptr<class Engine>;

class Engine {

    public:
        Engine() = default;
        
        virtual std::string getChipModuleList() const = 0;
        virtual std::string getVHDLParsingResult() const = 0;
        virtual std::string getSimulationResult(std::string vhdl_source_code) const = 0;
        
        /* add chip modules from a given file
         * the list file is a .txt file which contains several lines
         * each line represents a chip's name
         * the modules' VHDL codes and the list file are in the directiory <path>
         * the VHDL files are written in specific formats
         * see data/vhdl
         * example: addChipModules("data/vhdl", "chip_list.txt");
         * retval: the total count of modules added
         **/
        virtual int addChipModules(std::string path, std::string file) = 0;
        
        static EnginePtr createEngine(std::string out_path);
         
        Engine(const Engine &) = delete;
        void operator=(const Engine &) = delete;
        
};

} // namespace psjjjj

