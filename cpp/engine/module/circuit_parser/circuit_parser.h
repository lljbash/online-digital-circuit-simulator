#pragma once

#include "util/util.h"
#include "module/mod_organizer/mod_organizer.h"
#include "circuit.pb.h"
#include "circuit_parsing_result.pb.h"

namespace psjjjj {

namespace test {
    class CircuitParserTest; // just for test
} // namespace test;

class CircuitParser {

    public:
        CircuitParser(std::shared_ptr<const ModOrganizer> mod_organizer);
        
        CircuitParsingResultProto parse();
        
        friend test::CircuitParserTest;
    
    private:
        std::string generatePinMapping(const util::ChipStatus &status) const; 
        
        std::shared_ptr<const ModOrganizer> mod_organizer_;

};

} // namespace psjjjj

