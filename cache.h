#ifndef INCLUDED_CACHE
#define INCLUDED_CACHE

#include <chrono>
#include <string>
#include <unordered_map>
#include <utility>

namespace Oso {

class TTLCache {
  public:
    using Duration  = std::chrono::duration<int>; // Duration int seconds

    /**
     * @brief constructor optionally takes a default time to live for all values in the cache
     * @param defaultTtlSeconds an optional default time to live, specified in seconds.
     *        0 indicates values do not expire. This can be overriden by using the set function
     *        and specifying a ttl
     */
    explicit TTLCache(Duration defaultTtlSeconds = Duration{});
    virtual ~TTLCache() {}

    /**
     * @brief sets a key value pair in the cache with a given time to live
     * @param ttl "time to live", the value given will expire after this time
     *        when 0, this value does not expire. This value overrides the default
     *        ttl for this key-value pair only 
     */
    void  set(const std::string& key, const std::string& value, Duration ttl);
    void  set(const std::string& key, const std::string& value);

    /**
     * @brief gets the value for the corresponding value for the given key
     * @return an "optional" string corresponding to the value given. a false value
     *         denotes a cache miss, indicating the value passed back is invalid
     */
    std::pair<std::string, bool> get(const std::string& key);

  private:
    using TimePoint = std::chrono::time_point<std::chrono::system_clock, Duration>;
    
    /**
     * @brief simple struct that holds a string corresponding to a value in the cache as well
     *        as the expiration time for that value
     */
    struct CacheValue {
        explicit CacheValue(const std::string& v = "", Duration d = Duration{});
        std::string value;              // value stored in the cache
        TimePoint   expiration;         // point in time when this value expires
        bool        expires;            // true if this value has an expiration date
    };

    // cache maps request strings to values with a time at which the value becomes invalid
    using CacheType = std::unordered_map<std::string, CacheValue>;
    using CacheTypeVal = CacheType::value_type;
    CacheType   d_cache;
    Duration    d_defaultTtl;
};

} // namespace Oso

#endif
