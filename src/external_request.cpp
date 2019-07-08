#include <chrono> // std::chrono::microseconds
#include <exception>
#include <future>
#include <sstream>
#include <stdlib.h>
#include <thread> // std::this_thread::sleep_for;

#include "external_request.h"

namespace Oso {

namespace {

std::string create_random_token()
{
    std::string s;
    for (int i = 0; i < 10; ++i) {
        s.push_back('a' + (rand() % 26));
    }
    return s;
}

} // anonymous namespace

std::future<std::string> ExternalRequest::query(const Data& request_data)
{
    return std::async(&ExternalRequest::query_impl, *this, request_data);
}

std::string ExternalRequest::query_impl(const Data& request_data)
{
    std::string query_str = create_query_str(request_data);
    return fetch_token_from_server(query_str);
}

std::string ExternalRequest::create_query_str(const Data& data) const
{
    std::stringstream ss;
    ss << data.d_request_type << ':' << data.d_user << ':' << data.d_key;
    return ss.str();
}

std::string ExternalRequest::fetch_token_from_server(const std::string& query_str) const
{
    // request takes somewhere between 1 and 3 seconds
    std::chrono::milliseconds ms{rand() % 2000 + 1000};
    std::this_thread::sleep_for(ms);

    // throw randomly
    if (0 == ms.count() % 10) {
        throw std::runtime_error("Could not fetch token from server!");
    }

    return create_random_token();
}

} // namespace Oso