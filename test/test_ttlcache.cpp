#include "gtest/gtest.h"
#include "cache.h"

#include <chrono>
#include <string>
#include <thread>

using namespace Oso;
using RETURN = std::pair<std::string, bool>;

TEST(CacheTest, DefaultCache_SetAndCacheHit)
{
    // GIVEN
    TTLCache c;
    std::string key = "key";
    std::string value = "value";

    // WHEN
    c.set(key, value);
    RETURN r = c.get(key);

    // THEN
    EXPECT_EQ(value, r.first);
    EXPECT_TRUE(r.second);
}

TEST(CacheTest, DefaultCache_SetAndCacheMiss)
{
    // GIVEN
    TTLCache c;
    std::string key = "key";
    std::string value = "value";
    std::string not_key = "bad_key";

    // WHEN
    c.set(key, value);
    RETURN r = c.get(not_key);

    // THEN
    EXPECT_FALSE(r.second);
}

TEST(CacheTest, DefaultCache_TwoValsSetAndHit)
{
    // GIVEN
    TTLCache c;
    std::string k1 = "k1", k2 = "k2";
    std::string v1 = "v1", v2 = "v2";

    // WHEN
    c.set(k1, v1);
    c.set(k2, v2);
    RETURN r1 = c.get(k1);
    RETURN r2 = c.get(k2);

    // THEN
    EXPECT_EQ(v1, r1.first);
    EXPECT_TRUE(r1.second);
    EXPECT_EQ(v2, r2.first);
    EXPECT_TRUE(r2.second);

}

TEST(CacheTest, DefaultCache_SetAndReset)
{
    // GIVEN
    TTLCache c;
    std::string key = "key";
    std::string v1 = "v1";
    std::string v2 = "v2";

    // WHEN
    c.set(key, v1);
    c.set(key, v2);
    RETURN r = c.get(key);

    // THEN
    EXPECT_EQ(v2, r.first);
    EXPECT_TRUE(r.second);
}

TEST(CacheTest, ExpiringVal_CacheHit)
{
    // GIVEN
    TTLCache c{Duration{5}}; // 5 sec expiry
    std::string key = "key";
    std::string value = "value";

    // WHEN
    c.set(key, value);
    RETURN r = c.get(key);

    // THEN
    EXPECT_EQ(value, r.first);
    EXPECT_TRUE(r.second);
}

TEST(CacheTest, ExpiringVal_CacheMiss)
{
    // GIVEN
    TTLCache c{Duration{1}}; // small expiry
    std::string key = "key";
    std::string value = "value";

    // WHEN
    c.set(key, value);
    std::this_thread::sleep_for(std::chrono::seconds{2});
    RETURN r = c.get(key);

    // THEN
    EXPECT_FALSE(r.second);
}

TEST(CacheTest, ExpiringVal_CustomExpiry_CacheHit)
{
    // GIVEN
    TTLCache c{Duration{1}};
    std::string key = "key";
    std::string value = "value";

    // WHEN
    c.set(key, value, Duration{3});
    std::this_thread::sleep_for(std::chrono::seconds{2});
    RETURN r = c.get(key);

    // THEN
    EXPECT_EQ(value, r.first);
    EXPECT_TRUE(r.second);
}

TEST(CacheTest, ExpiringVal_CustomExpiry_CacheMiss)
{
    // GIVEN
    TTLCache c{Duration{5}};
    std::string key = "key";
    std::string value = "value";

    // WHEN
    c.set(key, value, Duration{1});
    std::this_thread::sleep_for(std::chrono::seconds{2});
    RETURN r = c.get(key);

    // THEN
    EXPECT_FALSE(r.second);
}

