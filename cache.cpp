#include "cache.h"
#include <chrono>
#include <utility>

namespace Oso {

namespace {
std::chrono::time_point<std::chrono::system_clock, TTLCache::Duration> now() {
    return std::chrono::time_point_cast<TTLCache::Duration>(std::chrono::system_clock::now());
}
} // anonymous namespace

TTLCache::TTLCache(Duration defaultTtlSeconds)
: d_cache()
, d_defaultTtl(defaultTtlSeconds)
{
    // noop
}

void  TTLCache::set(const std::string& key, const std::string& value, Duration ttl)
{
    d_cache[key] = CacheValue{value, ttl};
}

void  TTLCache::set(const std::string& key, const std::string& value)
{
    d_cache[key] = CacheValue{value, d_defaultTtl};
}

std::pair<std::string, bool> TTLCache::get(const std::string& key)
{
    std::pair<std::string, bool> ret;

    auto it = d_cache.find(key);
    if (it == d_cache.end()) {
        ret.second = false;
    } else {
        ret.second = true;
        ret.first  = it->second.value;
    }

    return ret;
}

TTLCache::CacheValue::CacheValue(const std::string& v, Duration d)
: value{v}
, expiration{d.count() ? now() + d : TimePoint{}}
, expires{d.count() ? true : false}
{
    // noop
}

} // namespace Oso