#ifndef INCLUDED_CACHED_REQUEST
#define INCLUDED_CACHED_REQUEST

#include "cache.h"
#include "external_request.h"
#include "request_types.h"

namespace Oso {

class CachedRequest : public ExternalRequest {
  public:

    CachedRequest(const std::shared_ptr<TTLCache>& cache, const std::shared_ptr<RequestTypes>& rTypes);

    /**
     * @brief makes external request to server to get data and caches the value
     *        throws an exception if this module cannot connect to the server (on a cache miss)
     * @copydoc Request::query
     */
    std::string query(const Data& requestData) override;

  private:
    std::shared_ptr<TTLCache>       d_cache;
    std::shared_ptr<RequestTypes>   d_request_types;
};

} // namespace Oso

#endif
