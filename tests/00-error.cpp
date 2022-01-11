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

static nio::Result<int, int> check(bool success) {
	nio::Result<int, int> ret;
	return (success) ? ret.Ok(0) : ret.Err(-1);
}

TEST_CASE("nio error handler tests", "[nio]") {
	TEST_ERRNO(EPERM);
	TEST_ERRNO(ENOENT);
	TEST_ERRNO(ESRCH);
	TEST_ERRNO(EINTR);

	SECTION("Test nio::Result", "[nio]") {
		auto r = check(true);
		REQUIRE(r.is_ok() == true);
		REQUIRE(r.is_err() == false);
		REQUIRE(r.Ok() == 0);

		r = check(false);
		REQUIRE(r.is_ok() == false);
		REQUIRE(r.is_err() == true);
		REQUIRE(r.Err() == -1);
	}
}