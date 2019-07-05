#include "cached_request.h"

namespace Oso {

CachedRequest::CachedRequest(const std::shared_ptr<TTLCache>& cache)
: d_cache(cache)
{
    // noop
}

std::string CachedRequest::query(const Data& requestData)
{
    // check the cache first
    std::string key = ExternalRequest::create_query_str(requestData);
    std::pair<std::string, bool> cacheRet = d_cache->get(key);
    if (cacheRet.second) {
        return cacheRet.first;
    }

    // external fetch for cache miss
    std::string value = ExternalRequest::query(requestData);

    // cache
    d_cache->set(key, value);

    return value;
}

} // namespace Oso