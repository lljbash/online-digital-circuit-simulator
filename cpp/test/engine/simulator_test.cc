#include "gtest/gtest.h"
#include "module/simulator/simulator.h"

using namespace std;

namespace psjjjj {
namespace test {

class SimulatorTest : public ::testing::Test {

    protected:
        virtual void SetUp() override {
            simulator.reset(new Simulator());
        }
        virtual void TearDown() override {
            
        }
        
        unique_ptr<Simulator> simulator;

};

TEST_F(SimulatorTest, SimpleTest) {
    FILE *vhdl_file = fopen("data/test/engine/simulator/test.vhd", "r");
    char code[999];
    fread(code, sizeof(char), 999, vhdl_file);
    fclose(vhdl_file);
    SimulationResultProto srp = simulator->simulate(code, "../tmp");
    cout << srp.success() << endl;
    cout << srp.file_name() << endl;
}

TEST_F(SimulatorTest, FailTest) {
    SimulationResultProto srp = simulator->simulate("fuck", "../tmp");
    cout << srp.success() << endl;
    cout << srp.error_message() << endl;
}

} // namespace test
} // namespace psjjjj

