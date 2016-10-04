#pragma once

#include <string>
#include <memory>

namespace psjjjj {

using EnginePtr = std::unique_ptr<class Engine>;

class Engine {

    public:
        Engine() = default;
        
        virtual std::string hello() const = 0;
        
        static EnginePtr generateEngine();
         
        Engine(const Engine &) = delete;
        void operator=(const Engine &) = delete;
        
};

} // namespace psjjjj

