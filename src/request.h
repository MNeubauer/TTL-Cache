#ifndef INCLUDED_REQUEST
#define INCLUDED_REQUEST

#include <future>
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
     * @return a future to the token or value that is being requested
     */
    virtual std::future<std::string> query(const Data& request_data) = 0;

    /**
     * @brief helper that creates the actual request for this external resource
     */
    virtual std::string create_query_str(const Data& request_data) const = 0;

};

} // namespace Oso

#endif
