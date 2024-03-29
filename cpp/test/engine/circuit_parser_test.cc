#include "gtest/gtest.h"
#include "module/circuit_parser/circuit_parser.h"

using namespace std;

namespace psjjjj {
namespace test {

class CircuitParserTest : public ::testing::Test {

    protected:
        virtual void SetUp() override {
            mod_organizer.reset(new ModOrganizer());
            circuit_parser.reset(
                new CircuitParser(const_pointer_cast<const ModOrganizer>(mod_organizer))
            );
            mod_organizer->load_modules("data/vhdl", "chip_list.txt");
        }
        virtual void TearDown() override {
            
        }
        
        string generatePinMapping(const util::ChipStatus &status) {
            return circuit_parser->generatePinMapping(status);
        }
        
        unique_ptr<CircuitParser> circuit_parser;
        shared_ptr<ModOrganizer> mod_organizer;

};

TEST_F(CircuitParserTest, GeneratePinMapping) {
    util::ChipStatus status;
    status.type = "NAND_GATE2";
    status.pin["X"] = "input1";
    status.pin["Y"] = "input2";
    status.pin["F2"] = "output";
    cout << generatePinMapping(status) << endl;
}

TEST_F(CircuitParserTest, GenerateHangedPinMapping) {
    util::ChipStatus status;
    status.type = "MOD_74LS20";
    status.pin["X1"] = "input1";
    status.pin["X2"] = "input2";
    status.pin["X4"] = "input3";
    status.pin["X5"] = "input4";
    status.pin["Y6"] = "output";
    cout << generatePinMapping(status) << endl;
}

TEST_F(CircuitParserTest, ParseSimpleCircuit) {
    CircuitProto circuit;
    auto chip = circuit.add_chips();
    chip->set_type("input");
    chip->set_id("input");
    chip = circuit.add_chips();
    chip->set_type("output");
    chip->set_id("output");
    auto wire = circuit.add_wires();
    CircuitProto::Wire::Pin *pin = new CircuitProto::Wire::Pin;
    pin->set_chip_name("input");
    wire->set_allocated_start_pin(pin);
    pin = new CircuitProto::Wire::Pin;
    pin->set_chip_name("output");
    wire->set_allocated_end_pin(pin);
    cout << circuit_parser->parse(circuit).vhdl_code();
}

TEST_F(CircuitParserTest, ParseSimpleCircuitiWithActivation) {
    CircuitProto circuit;
    auto chip = circuit.add_chips();
    chip->set_type("input");
    chip->set_id("input");
    auto act = new CircuitProto::Chip::Activation;
    act->set_initial(false);
    chip->set_allocated_activation(act);
    chip = circuit.add_chips();
    chip->set_type("output");
    chip->set_id("output");
    auto wire = circuit.add_wires();
    CircuitProto::Wire::Pin *pin = new CircuitProto::Wire::Pin;
    pin->set_chip_name("input");
    wire->set_allocated_start_pin(pin);
    pin = new CircuitProto::Wire::Pin;
    pin->set_chip_name("output");
    wire->set_allocated_end_pin(pin);
    cout << circuit_parser->parse(circuit).vhdl_code();
}

} // namespace test
} // namespace psjjjj

