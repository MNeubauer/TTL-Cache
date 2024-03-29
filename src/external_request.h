#ifndef INCLUDED_EXTERNAL_REQUEST
#define INCLUDED_EXTERNAL_REQUEST

#include "request.h"
#include <future>

namespace Oso {

class ExternalRequest : public Request {
  public:

    /**
     * @brief makes external request to server to get data
     *        throws an exception if this module cannot connect to the server
     * @copydoc Request::query
     */
    std::future<std::string> query(const Data& request_data) override;

    /**
     * @copydoc Request::create_query_str
     */
    std::string create_query_str(const Data& request_data) const override;

  private:

    /**
     * @copydoc ExternalRequest::query
     */
    std::string query_impl(const Data& request_data);

    /**
     * @brief makes an out of process call to fetch a token
     */
    std::string fetch_token_from_server(const std::string& query_str) const;
};

} // namespace Oso

#endif
