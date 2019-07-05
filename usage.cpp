#include <chrono>
#include <iostream>
#include <memory>

#include "cache.h"
#include "cached_request.h"
#include "external_request.h"
#include "request.h"

Oso::Request::Data createRandomReq();
void makeTimedCall(Oso::Request& r, const Oso::Request::Data& data);

int main() {
    std::cout << "Hello, World!" << std::endl;

    // setup
    std::unique_ptr<Oso::Request> externalReq{new Oso::ExternalRequest};
    constexpr int OneDayInSeconds = 60 * 60 * 24;
    std::shared_ptr<Oso::TTLCache> cache{new Oso::TTLCache{Oso::TTLCache::Duration{OneDayInSeconds}}};
    std::unique_ptr<Oso::Request> cachedReq{new Oso::CachedRequest{cache}};

    // slow call without cache
    Oso::Request::Data data = createRandomReq();

    makeTimedCall(*externalReq, data);
    makeTimedCall(*externalReq, data);
    makeTimedCall(*cachedReq, data);
    makeTimedCall(*cachedReq, data);

    // get promise 1
    // get promise 2

    // do this again, and show that the cache is faster

    // do it again, again, and show that the cache needed to refresh

    return 0;
}

Oso::Request::Data createRandomReq()
{
    return Oso::Request::Data{"getTokenA", "user1", 123};
}

void makeTimedCall(Oso::Request& r, const Oso::Request::Data& data)
{
    auto start{std::chrono::system_clock::now()};
    std::string token{r.query(data)};
    auto duration = std::chrono::system_clock::now() - start;

    std::cout << "Token received token=" << token << " in duration=" << duration.count() / 1000.0 << " ms" << std::endl;

}
