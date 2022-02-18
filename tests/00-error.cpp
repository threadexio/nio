#include <iostream>

#include "catch.hpp"
#include "nio/error.hpp"

#define IP	 "127.0.0.24"
#define PORT 8888

void i_throw() {
	NIO_THROW_ERROR(nio::error);
}

void i_throw_io() {
	NIO_THROW_ERROR(nio::io_error);
}

void i_throw_custom() {
	NIO_THROW_ERROR_CUSTOM(nio::error, -1);
}

TEST_CASE("nio error handling tests", "[nio]") {
	try {
		i_throw_io();
	} catch (const nio::io_error& e) {
		REQUIRE(strcmp(e.which(), "i_throw_io") == 0);
		REQUIRE(e.err() == 0);
	}

	try {
		i_throw();
	} catch (const nio::error& e) {
		REQUIRE(strcmp(e.which(), "i_throw") == 0);
		REQUIRE(e.err() == 0);
	}

	try {
		i_throw_custom();
	} catch (const nio::error& e) {
		REQUIRE(strcmp(e.which(), "i_throw_custom") == 0);
		REQUIRE(e.err() == -1);
	}
}