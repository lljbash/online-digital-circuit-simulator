#include "gtest/gtest.h"
#include "module/circuit_parser/circuit_parser.h"

using namespace std;

namespace psjjjj {
namespace test {

class CircuitParserTest : public ::testing::Test {

    protected:
        virtual void SetUp() override {
            circuit_parser.reset(new CircuitParser());
        }
        virtual void TearDown() override {
            
        }
        
        string generatePinMapping(const util::ChipStatus &status) {
            return circuit_parser->generatePinMapping(status);
        }
        
        unique_ptr<CircuitParser> circuit_parser;

};

TEST_F(CircuitParserTest, GeneratePinMapping) {
    util::ChipStatus status;
    status.type = "NAND_GATE2";
    status.pin["X"] = "input1";
    status.pin["Y"] = "input2";
    status.pin["F2"] = "output";
    cout << generatePinMapping(status) << endl;
}

} // namespace test
} // namespace psjjjj

