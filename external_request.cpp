#include <chrono> // std::chrono::microseconds
#include <sstream>
#include <stdlib.h>
#include <thread> // std::this_thread::sleep_for;

#include "external_request.h"

using std::chrono::microseconds;
using std::string;
using std::stringstream;
using std::this_thread::sleep_for;

namespace Oso {

namespace {

string create_random_token()
{
    string s;
    for (int i = 0; i < 10; ++i) {
        s.push_back('a' + (rand() % 26));
    }
    return s;
}

} // anonymous namespace
string ExternalRequest::query(const Data& requestData)
{
    string query_str = create_query_str(requestData);
    return fetch_token_from_server(query_str);
}

string ExternalRequest::create_query_str(const Data& data) const
{
    stringstream ss;
    ss << data.d_request_type << ':' << data.d_user << ':' << data.d_key;
    return ss.str();
}

string ExternalRequest::fetch_token_from_server(const string& query_str) const
{
    // request takes somewhere between 1 and 3 seconds
    sleep_for(microseconds{rand() % 2000000 + 1000000});
    return create_random_token();
}

} // namespace Oso