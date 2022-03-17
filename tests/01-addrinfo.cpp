#include <iostream>

#include "catch.hpp"
#include "nio/ip/v4/addr.hpp"
#include "nio/ip/v6/addr.hpp"

TEST_CASE("nio address resolver tests", "[nio]") {
	try {
		for (auto& a : nio::ip::v4::resolve("localhost")) {
			std::cout << a.to_string() << "\n";
			REQUIRE(a.ip() == "127.0.0.1");
		}

		for (auto& a : nio::ip::v6::resolve("localhost")) {
			std::cout << a.to_string() << "\n";
			REQUIRE(a.ip() == "::1");
		}

	} catch (const nio::error& e) {
		std::cout << e.err() << ": " << e.which() << ": " << e.what() << "\n";
	}
}