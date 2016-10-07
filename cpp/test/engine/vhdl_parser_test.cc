#include "gtest/gtest.h"
#include "module/vhdl_parser/vhdl_parser.h"

using namespace std;

namespace psjjjj {
namespace test {

class VHDLParserTest : public ::testing::Test {

    protected:
        virtual void SetUp() override {
            parser.reset(new VHDLParser());
        }
        virtual void TearDown() override {
            
        }
        
        unique_ptr<VHDLParser> parser;

};

TEST_F(VHDLParserTest, SimpleTest) {
    VHDLParsingResultProto vrp = parser->parse();
    cout << vrp.success() << endl;
    cout << vrp.vhdl_code() << endl;
}

} // namespace test
} // namespace psjjjj

