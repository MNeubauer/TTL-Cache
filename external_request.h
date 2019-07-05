#ifndef INCLUDED_EXTERNAL_REQUEST
#define INCLUDED_EXTERNAL_REQUEST

#include "request.h"

namespace Oso {

class ExternalRequest : public Request {
  public:

    /**
     * @brief makes external request to server to get data
     *        throws an exception if this module cannot connect to the server
     * @copydoc Request::query
     */
    std::string query(const Data& requestData) override;

  protected:
    /**
     * @brief helper that creates the actual request for this external resource
     *        private as the client has no need to know about how to construct this string
     */
    std::string create_query_str(const Data& requestData) const;

  private:
    /**
     * @brief makes an out of process call to fetch a token
     */
    std::string fetch_token_from_server(const std::string& query_str) const;
};

} // namespace Oso

#endif
