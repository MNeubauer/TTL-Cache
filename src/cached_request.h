#ifndef INCLUDED_CACHED_REQUEST
#define INCLUDED_CACHED_REQUEST

#include "cache.h"
#include "request.h"
#include "request_types.h"

namespace Oso {

class CachedRequest : public  Request {
  public:

    CachedRequest(const std::shared_ptr<TTLCache>& cache,
                  const std::shared_ptr<Request>& request,
                  const std::shared_ptr<RequestTypes>& rTypes,
                  int max_fetch_retries = 0);

    /**
     * @brief makes external request to server to get data and caches the value
     *        throws an exception if this module cannot connect to the server (on a cache miss)
     * @copydoc Request::query
     */
    std::future<std::string> query(const Data& request_data) override;

    /**
     * @copydoc Request::create_query_str
     * This utilizes the create_query_str function from the slow request
     */
    std::string create_query_str(const Data& request_data) const override;
  private:
    std::shared_ptr<TTLCache>       d_cache;
    std::shared_ptr<Request>        d_slow_request;
    std::shared_ptr<RequestTypes>   d_request_types;
    int                             d_max_attempts; // 1 more than # of retries

    /**
     * @copydoc CachedRequest::query
     */
    std::string query_impl(const Data& requestData);
};

} // namespace Oso

#endif
