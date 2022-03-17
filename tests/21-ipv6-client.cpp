#include <iostream>

#include "catch.hpp"
#include "nio/ip/v6/client.hpp"
#include "nio/types.hpp"

#define IP	 "::1"
#define PORT 8888

TEST_CASE("nio::ip::v6::client tests", "[nio]") {
	try {
		nio::ip::v6::client cli(nio::ip::v6::addr(IP, PORT));

		cli.create();

		nio::ip::v6::stream stream;
		stream = cli.connect();

		std::cout << "Server: " << stream.peer().ip() << ":"
				  << stream.peer().port() << "\n";

		REQUIRE(stream.peer().ip() == IP);

		const char* testdata = "abcdefg\n\r\b\a!DSFDSW23423";

		// stream.write(testdata, strlen(testdata));
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