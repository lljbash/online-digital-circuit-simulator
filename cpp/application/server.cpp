#include <iostream>
#include "engine.h"

using namespace psjjjj;
using namespace std;

int main() {
    EnginePtr engine = Engine::generateEngine();
    
    cout << engine->hello() << endl;
    
    return 0;
}

