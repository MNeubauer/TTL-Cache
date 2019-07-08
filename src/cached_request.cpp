#include "cached_request.h"
#include <iostream>

namespace Oso {

CachedRequest::CachedRequest(const std::shared_ptr<TTLCache>& cache,
                             const std::shared_ptr<RequestTypes>& req_types,
                             int max_fetch_retries)
: d_cache{cache}
, d_request_types{req_types}
, d_max_attempts{max_fetch_retries + 1}
{
    // noop
}

std::future<std::string> CachedRequest::query(const Data& request_data)
{
    return std::async(&CachedRequest::query_impl, *this, request_data);
}


std::string CachedRequest::query_impl(const Data& request_data)
{
    // check the cache first
    std::string key = ExternalRequest::create_query_str(request_data);
    std::pair<std::string, bool> cache_ret = d_cache->get(key);
    if (cache_ret.second) {
        return cache_ret.first;
    }

    for (int i = 0; i < d_max_attempts; ++i) {
        try {
            // external fetch for cache miss            
            std::future<std::string> value_promise = ExternalRequest::query(request_data);
            std::string value = value_promise.get();
            d_cache->set(key, value, d_request_types->get_time_to_live(request_data.d_request_type));
            return value;
        }
        catch (std::runtime_error& err) {
            std::cout << "Caught a runtime exception on attempt number " << i + 1;
            if (i + 1 < d_max_attempts) {
                std::cout << ". Retrying!" << std::endl;
            }
            else {
                std::cout << " and have reached the maximum number of retries!" << std::endl;
                throw;
            }
        }
    }

    throw std::runtime_error("Programmer error, this is never hit");
}

} // namespace Oso