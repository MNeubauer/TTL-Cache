#ifndef INCLUDED_REQUEST
#define INCLUDED_REQUEST

#include <string>

namespace Oso {

class Request {
  public:

    struct Data {
        // constructors
        Data();
        Data(const std::string& request_type, const std::string& user, int key);

        // public data
        std::string d_request_type;
        std::string d_user;
        int d_key;
    };

    virtual ~Request() {}

    /**
     * @brief fetches a request string and returns the value.
     *        If the request fails, an exception may be thrown.
     * @param requestString request that will be fulfilled by this Request Object
     * @return the token or value that is being requested
     */
    virtual std::string query(const Data& requestData) = 0;
};

} // namespace Oso

#endif
