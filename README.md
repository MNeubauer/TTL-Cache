# TTL-Cache

- build
```make build```
- run sample usage
```./build/usage.out```
- build and run tests
```make test```

## sample test output
```sh
$ make test
clang++ -std=c++14 -stdlib=libc++ -o build/test.out \
		-Isrc/  -I/Users/natashahnanus/.matt/googletest/googletest/include/ -I/Users/natashahnanus/.matt/googletest/googlemock/include/ \
		src/cache.cpp test/test_ttlcache.cpp \
		-L/Users/natashahnanus/.matt/googletest/build/lib -lgtest_main -lgtest -lgmock_main -lgmock \
		--debug
./build/test.out
Running main() from /Users/natashahnanus/.matt/googletest/googletest/src/gtest_main.cc
[==========] Running 8 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 8 tests from CacheTest
[ RUN      ] CacheTest.DefaultCache_SetAndCacheHit
[       OK ] CacheTest.DefaultCache_SetAndCacheHit (0 ms)
[ RUN      ] CacheTest.DefaultCache_SetAndCacheMiss
[       OK ] CacheTest.DefaultCache_SetAndCacheMiss (0 ms)
[ RUN      ] CacheTest.DefaultCache_TwoValsSetAndHit
[       OK ] CacheTest.DefaultCache_TwoValsSetAndHit (0 ms)
[ RUN      ] CacheTest.DefaultCache_SetAndReset
[       OK ] CacheTest.DefaultCache_SetAndReset (0 ms)
[ RUN      ] CacheTest.ExpiringVal_CacheHit
[       OK ] CacheTest.ExpiringVal_CacheHit (0 ms)
[ RUN      ] CacheTest.ExpiringVal_CacheMiss
[       OK ] CacheTest.ExpiringVal_CacheMiss (2006 ms)
[ RUN      ] CacheTest.ExpiringVal_CustomExpiry_CacheHit
[       OK ] CacheTest.ExpiringVal_CustomExpiry_CacheHit (2000 ms)
[ RUN      ] CacheTest.ExpiringVal_CustomExpiry_CacheMiss
[       OK ] CacheTest.ExpiringVal_CustomExpiry_CacheMiss (2003 ms)
[----------] 8 tests from CacheTest (6010 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test suite ran. (6011 ms total)
[  PASSED  ] 8 tests.
```
