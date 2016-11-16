#include "gtest/gtest.h"
#include "module/vcd_parser/vcd_parser.h"

using namespace std;

namespace psjjjj {
namespace test {

class VcdParserTest : public ::testing::Test {

    protected:
        virtual void SetUp() override {
            vcd_parser.reset(new VcdParser());
        }
        virtual void TearDown() override {
            
        }
        
        unique_ptr<VcdParser> vcd_parser;

};

TEST_F(VcdParserTest, SimpleVcdParse) {
    char input[99999];
    FILE *file = fopen("data/test/engine/vcd_parser/test.vcd", "r");
    fread(input, 1, 99999, file);
    string code(input);
    string str = vcd_parser->parse(input);
    cout << str << endl;
    //cv::Mat mat = vcd_parser->parse(input);
    //cv::imwrite("test.png", mat);
}

} // namespace test
} // namespace psjjjj

