#include "gtest/gtest.h"
#include "module/mod_organizer/mod_organizer.h"

using namespace std;

namespace psjjjj {
namespace test {

class ModOrganizerTest : public ::testing::Test {

    protected:
        virtual void SetUp() override {
            mod_organizer.reset(new ModOrganizer());
        }
        virtual void TearDown() override {
            
        }
        
        void parse_module(const string &module_name,
                          istream &&module_code,
                          ChipModuleProto *chip_module) {
            mod_organizer->parse_module(module_name, move(module_code), chip_module);
        }
        
        unique_ptr<ModOrganizer> mod_organizer;

};

TEST_F(ModOrganizerTest, ParseSingleModule) {
    ifstream vhdl_in("data/vhdl/MOD_74LS00.vhd");
    ASSERT_TRUE(vhdl_in.is_open());
    ChipModuleProto chip_module;
    parse_module("MOD_74LS00", move(vhdl_in), &chip_module);
    cout << chip_module.DebugString() << endl;
    cout << chip_module.port_code() << endl;
    cout << chip_module.entity_code() << endl;
}

TEST_F(ModOrganizerTest, LoadModuleList) {
    mod_organizer->clear_modules();
    int cnt = mod_organizer->load_modules("data/vhdl", "chip_list.txt");
    ChipModuleListProto mod_list;
    mod_list.ParseFromString(mod_organizer->getModuleList());
    cout << mod_list.DebugString() << endl;
    cout << "Total Count: " << cnt << endl;
}

} // namespace test
} // namespace psjjjj

