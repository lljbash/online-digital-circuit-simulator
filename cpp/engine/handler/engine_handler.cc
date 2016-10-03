#include "engine_handler.h"

using namespace psjjjj;
using namespace std;

EnginePtr Engine::generateEngine() {
    return EnginePtr(new EngineHandler());
}

string EngineHandler::hello() const {
    return string("hello world");
}

