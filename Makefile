.PHONY: build test clean

all: build test

build:
	clang++ -std=c++14 -stdlib=libc++ -o build/usage.out src/usage.cpp src/request.cpp src/external_request.cpp src/cache.cpp src/cached_request.cpp src/request_types.cpp --debug

GOOG=/Users/natashahnanus/.matt/googletest
GLIB_DIR=${GOOG}/build/lib
GINCLUDES=-I${GOOG}/googletest/include/ -I${GOOG}/googlemock/include/

test:
	clang++ -std=c++14 -stdlib=libc++ -o build/test.out \
		-Isrc/  ${GINCLUDES} \
		src/cache.cpp test/test_ttlcache.cpp \
		-L${GLIB_DIR} -lgtest_main -lgtest -lgmock_main -lgmock \
		--debug
	./build/test.out

clean:
	rm -rf build/*

