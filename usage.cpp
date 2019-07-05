#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>

#include "cache.h"
#include "cached_request.h"
#include "external_request.h"
#include "request.h"
#include "request_types.h"

Oso::Request::Data createRandomReq();
void makeTimedCall(Oso::Request& r, const Oso::Request::Data& data, const std::string& requester);

int main() {
    srand(time(NULL));

    // setup
    std::unique_ptr<Oso::Request> externalReq{new Oso::ExternalRequest};
    constexpr int OneDayInSeconds = 60 * 60 * 24;
    std::shared_ptr<Oso::TTLCache> cache{new Oso::TTLCache{Oso::Duration{OneDayInSeconds}}};
    std::shared_ptr<Oso::RequestTypes> rqs{new Oso::RequestTypes};
    std::unique_ptr<Oso::Request> cachedReq{new Oso::CachedRequest{cache, rqs}};

    // slow call without cache
    Oso::Request::Data data = createRandomReq();

    makeTimedCall(*cachedReq, data, "cached");
    makeTimedCall(*cachedReq, data, "cached");
    makeTimedCall(*externalReq, data, "external");
    makeTimedCall(*externalReq, data, "external");
    makeTimedCall(*cachedReq, data, "cached");

    // get promise 1
    // get promise 2

    // do this again, and show that the cache is faster

    // do it again, again, and show that the cache needed to refresh

    return 0;
}

Oso::Request::Data createRandomReq()
{
    static Oso::RequestTypes rqs;
    return Oso::Request::Data{rqs.get_random_request_type(), "user1", 123};
}

void makeTimedCall(Oso::Request& r, const Oso::Request::Data& data, const std::string& requester)
{
    auto start{std::chrono::system_clock::now()};
    std::string token{r.query(data)};
    auto duration = std::chrono::system_clock::now() - start;

    std::cout << "Token received token=" 
              << token 
              << " in duration=" 
              << duration.count() / 1000.0 
              << " ms requestor="
              << requester 
              << std::endl;

}
