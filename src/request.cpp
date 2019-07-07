#include <sstream>
#include "request.h"


using std::stringstream;

namespace Oso {

Request::Data::Data()
: d_request_type()
, d_user()
, d_key(0)
{
    // noop
}

Request::Data::Data(const std::string& request_type, const std::string& user, int key)
: d_request_type(request_type)
, d_user(user)
, d_key(key)
{
    // noop
}

} // namespace Oso
