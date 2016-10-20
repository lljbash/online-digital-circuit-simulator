/* Definition of useful structs
 */

#pragma once

#include <string>
#include <map>

namespace psjjjj {
namespace util {

struct ChipStatus {
    std::string type;
    std::map<std::string, std::string> pin; // which wire each pin links to
};

} // namespace util
} // namespace psjjjj

