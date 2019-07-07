#ifndef INCLUDED_REQUEST_TYPES
#define INCLUDED_REQUEST_TYPES

#include <chrono>
#include <stdlib.h>
#include <string>
#include <unordered_map>

namespace Oso {

// Duration in seconds
using Duration  = std::chrono::duration<int>;

class RequestTypes {
  public:
    RequestTypes();
    virtual ~RequestTypes() {}
    virtual std::string get_random_request_type() const;
    virtual Duration get_time_to_live(const std::string& reqType) const;

  private:
    using Durations = std::unordered_map<std::string, Duration>;
    Durations d_durations;
};

} // namespace Oso

#endif