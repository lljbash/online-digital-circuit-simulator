#pragma once

#include "util/util.h"
#include "module.pb.h"

namespace psjjjj {

namespace test {
class ModOrganizerTest; // only for test, see cpp/test/engine
} // namespace test

class ModOrganizer {

    public:
        ModOrganizer();
        
        /* retval: serialized ChipModuleListProto
         **/
        std::string getModuleList() const;
        
        /* get pin list of given module
         **/
        std::vector<ChipModuleProto::Pin> getPinList(std::string name) const;
        
        /* generate VHDL entity code for given module type
         * format:
         *   <entity_code>
         */
        std::string generateEntityCodeForModule(std::string name) const;
        
        /* generate VHDL component code for given module type
         * format:
         *   component <name>
         *   <port_code>
         *   end component;
         */
        std::string generateComponentCodeForModule(std::string name) const;
        
        /* load modules listed in a given file
         * modules' codes are placed in the given path
         * the codes need to be written in a specific format
         * see cpp/data/vhdl for more infomation
         * retval: the number of modules loaded
         **/
        int load_modules(const std::string &module_path,
                         const std::string &module_list_file);
        
        /* clear all stored modules
         **/ 
        void clear_modules();
        
        friend test::ModOrganizerTest;
    
    private:
        void parse_module(const std::string &module_name,
                          std::istream &&module_code,
                          ChipModuleProto *chip_module);
        
        std::unique_ptr<ChipModuleListProto> mod_list_;
        std::map<std::string, int> mod_id_;

};

} // namespace psjjjj

