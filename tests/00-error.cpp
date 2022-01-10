#include <errno.h>

#include "catch.hpp"
#include "nio/error.hpp"

#define TEST_ERRNO(x)                                                          \
	{                                                                          \
		SECTION("Testing error " #x, "[nio]") {                                \
			nio::Error error(x);                                               \
			REQUIRE(error.no == x);                                            \
			REQUIRE(error.msg == strerror(x));                                 \
		}                                                                      \
	}

TEST_CASE("nio::Error tests", "[nio]") {
	TEST_ERRNO(EPERM);
	TEST_ERRNO(ENOENT);
	TEST_ERRNO(ESRCH);
	TEST_ERRNO(EINTR);
}