#include <iostream>

#include "catch.hpp"
#include "nio/types.hpp"
#include "nio/unx/client.hpp"

#define PATH "/tmp/test.sock"

TEST_CASE("nio::unx::client tests", "[nio]") {
	try {
		nio::unx::client cli(nio::unx::addr(PATH));

		cli.create();

		nio::unx::stream stream;
		stream = cli.connect();

		const char* testdata = "abcdefg\n\r\b\a!DSFDSW23423";

		stream << testdata;

		std::unique_ptr<char[]> buf(new char[256]);
		stream.read(buf.get(), 255);

		REQUIRE(strncmp(testdata, buf.get(), 255) == 0);
	} catch (const nio::io_error& e) {
		std::cout << e.err() << ": " << e.which() << ": IO failed with \""
				  << e.what() << "\"\n";
		REQUIRE(false);
	} catch (const nio::error& e) {
		std::cout << e.err() << ": " << e.which() << ": failed with \""
				  << e.what() << "\"\n";
		REQUIRE(false);
	}
}