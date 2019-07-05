#include "request_types.h"
#include <iostream>
#include <iterator>
#include <stdlib.h>

namespace Oso {

using Durations = std::unordered_map<std::string, Duration>;

namespace {
const Durations::value_type durations[] = {
        Durations::value_type{"getToken", Duration{1}}, 
        Durations::value_type{"getUserAuthentication", Duration{2}},
        Durations::value_type{"verifyUser", Duration{2}},
        Durations::value_type{"verifyThirdPary", Duration{60}}
};
} // anonymous namespace

RequestTypes::RequestTypes()
: d_durations{std::cbegin(durations), std::cend(durations)}
{
    // noop
}

std::string RequestTypes::get_random_request_type() const
{
    return durations[rand() % (std::cend(durations) - std::cbegin(durations))].first;
}

Duration RequestTypes::get_time_to_live(const std::string& req_type) const
{
    auto it = d_durations.find(req_type);
    if (it == d_durations.end()) {
        // one second time to live for unknown requests
        std::cout << "unkown request_type=" << req_type << " duration=" << 1 << std::endl;
        return Duration{1};
    }

    std::cout << "found request_type=" 
              << req_type
              << " duration="
              << it->second.count() 
              << std::endl;

    return it->second;
}


} // namespace Oso