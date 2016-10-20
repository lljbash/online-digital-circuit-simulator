#pragma once

#include "util/util.h"
#include "module/mod_organizer/mod_organizer.h"
#include "circuit_parsing_result.pb.h"

namespace psjjjj {

namespace test {
    class CircuitParserTest; // just for test
} // namespace test;

class CircuitParser {

    public:
        static CircuitParsingResultProto parse();
        
        friend test::CircuitParserTest;
    
    private:
        std::string generatePinMapping(const util::ChipStatus &status) const; 

};

} // namespace psjjjj

