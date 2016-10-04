#pragma once

#include "engine.h"

namespace psjjjj {
    
class EngineHandler : public Engine {

    public:
        EngineHandler() = default;
        
        virtual std::string hello() const override;
        
};

} // namespace psjjjj

