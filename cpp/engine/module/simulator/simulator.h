#pragma once

#include "util/util.h"
#include "simulation_result.pb.h"

namespace psjjjj {

class Simulator {

    public:
        /* param: vhdl source code
         * retval: simulation result
         **/
        static SimulationResultProto simulate(std::string vhdl_source_code);

};

} // namespace psjjjj;

