#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>
#include <memory>
#include <thread>

#include "cache.h"
#include "cached_request.h"
#include "external_request.h"
#include "request.h"
#include "request_types.h"

Oso::Request::Data createRandomReq();
Oso::Request::Data createReqWithType(const std::string& req_type);
void makeTimedCall(Oso::Request& r, const Oso::Request::Data& data);
void makeTimedAsyncCalls(Oso::Request& r, const std::string& req_type);

const std::string ONE_SEC_REQ_TYPE = "1 Second Expiry";
const std::string TWO_SEC_REQ_TYPE = "2 Second Expiry";
const std::string FIVE_SEC_REQ_TYPE = "5 Second Expiry";
const std::string SIXTY_SEC_REQ_TYPE = "60 Second Expiry";

void explanatory_usage()
{
    // setup
    std::unique_ptr<Oso::Request> externalReq{new Oso::ExternalRequest};
    constexpr int OneDayInSeconds = 60 * 60 * 24;
    std::shared_ptr<Oso::TTLCache> cache{new Oso::TTLCache{Oso::Duration{OneDayInSeconds}}};
    std::shared_ptr<Oso::RequestTypes> rqs{new Oso::RequestTypes};
    std::unique_ptr<Oso::Request> cachedReq{new Oso::CachedRequest{cache, rqs}};

    // slow call without cache
    Oso::Request::Data data = createReqWithType(ONE_SEC_REQ_TYPE);

    try {
        std::cout << "Making a query sequentially without a cache" << std::endl;
        makeTimedCall(*externalReq, data);
        makeTimedCall(*externalReq, data);
        makeTimedCall(*externalReq, data);

        std::cout << "Now trying sequentially with a cache" << std::endl;
        makeTimedCall(*cachedReq, data);
        makeTimedCall(*cachedReq, data);
        makeTimedCall(*cachedReq, data);
    }
    catch(std::runtime_error& err) {
        std::cout << "Caught a runtime error '" << err.what() << "' moving on to next block" << std::endl;
    }

    try {
        std::cout << "Making a different query async without a cache" << std::endl;
        makeTimedAsyncCalls(*externalReq, SIXTY_SEC_REQ_TYPE);

        std::cout << "Making a different query async WITH a cache" << std::endl;
        makeTimedAsyncCalls(*cachedReq, SIXTY_SEC_REQ_TYPE);
    }
    catch(std::runtime_error& err) {
        std::cout << "Caught a runtime error '" << err.what() << "' moving on to next block" << std::endl;
    }

    std::cout << "That time didn't make much of a difference, but this time, we need to retrieve that same token!" << std::endl;

    try {
        std::cout << "Without the cache..." << std::endl;
        makeTimedAsyncCalls(*externalReq, SIXTY_SEC_REQ_TYPE);
        std::cout << "With the cache..." << std::endl;
        makeTimedAsyncCalls(*cachedReq, SIXTY_SEC_REQ_TYPE);
    }
    catch(std::runtime_error& err) {
        std::cout << "Caught a runtime error '" << err.what() << "' moving on to next block" << std::endl;
    }
}

void somewhat_realistic_usage(std::unique_ptr<Oso::Request> generic_requester)
{
    try {
        int number_of_times_some_work_must_be_done = 2;
        Oso::Request::Data req_data = createReqWithType(SIXTY_SEC_REQ_TYPE);
        for(int i = 0; i < number_of_times_some_work_must_be_done; ++i) {
            // step 1, call async request
            std::future<std::string> fut = generic_requester->query(req_data);
            // step 2, do other heavy lifting
            std::this_thread::sleep_for(std::chrono::milliseconds{rand() % 1000});
            // step 3, get future and do something with it.
            std::string token = fut.get();
            // do_something_with_token();
        }
    }
    catch(std::runtime_error& err) {
        std::cout << "Caught a runtime error '" << err.what() << "' and cannot proceed." << std::endl;
    }
}

int main() {
    srand(time(NULL));
    explanatory_usage();

    std::shared_ptr<Oso::TTLCache> cache{new Oso::TTLCache{}};
    std::shared_ptr<Oso::RequestTypes> rqs{new Oso::RequestTypes};
    std::unique_ptr<Oso::Request> request{new Oso::CachedRequest{cache, rqs}};
    somewhat_realistic_usage(std::move(request));

    return 0;
}

Oso::Request::Data createRandomReq()
{
    static Oso::RequestTypes rqs;
    return Oso::Request::Data{rqs.get_random_request_type(), "user1", 123};
}

Oso::Request::Data createReqWithType(const std::string& req_type)
{
    return Oso::Request::Data{req_type, "user1", 123};
}


void makeTimedCall(Oso::Request& r, const Oso::Request::Data& data)
{
    auto start{std::chrono::system_clock::now()};
    std::string token{r.query(data).get()};
    auto duration = std::chrono::system_clock::now() - start;

    std::cout << "Token received token=" 
              << token 
              << " in duration=" 
              << duration.count() / 1000.0 
              << " ms" 
              << std::endl;

}

void makeTimedAsyncCalls(Oso::Request& r, const std::string& req_type)
{
    Oso::Request::Data data = createReqWithType(req_type);
    auto start{std::chrono::system_clock::now()};
    std::future<std::string> token1 = r.query(data);
    std::future<std::string> token2 = r.query(data);
    std::future<std::string> token3 = r.query(data);
    token1.get();
    token2.get();
    token3.get();
    auto duration = std::chrono::system_clock::now() - start;
    std::cout << "Retrieved 3 different tokens in " << duration.count() / 1000.0 << " ms" << std::endl;
}
