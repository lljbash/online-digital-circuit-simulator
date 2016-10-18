#include "util.h"

using namespace std;

namespace psjjjj {
namespace util {

inline void trim(string &s) {
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
}

} // namespace util
} // namespace psjjjj

