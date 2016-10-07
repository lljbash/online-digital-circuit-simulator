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
    SimulationResultProto srp = simulator->simulate("hello world");
    cout << srp.success() << endl;
    cout << srp.file_name() << endl;
}

} // namespace test
} // namespace psjjjj

