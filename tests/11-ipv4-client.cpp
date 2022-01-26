#include <iostream>

#include "catch.hpp"
#include "nio/ip/stream.hpp"
#include "nio/ip/v4/client.hpp"

#define IP	 "127.0.0.24"
#define PORT 8888

static nio::ip::v4::client cli(nio::ip::v4::addr(IP, PORT));

TEST_CASE("nio::ip::v4::client tests", "[nio]") {
	if (auto r = cli.Create()) {
		std::cout << "Create(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}

	nio::ip::v4::stream stream;
	if (auto r = cli.Connect()) {
		std::cout << "Connect(): " << r.Err().msg << "\n";
		REQUIRE(false);
	} else {
		stream = r.Ok();
	}

	std::cout << "Server: " << stream.peer().ip() << ":" << stream.peer().port()
			  << "\n";

	REQUIRE(stream.peer().ip() == IP);

	const char* testdata = "abcdefg\n\r\b\a!DSFDSW23423";

	if (auto r = stream.write(testdata, strlen(testdata))) {
		std::cout << "write(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}

	std::unique_ptr<char[]> buf(new char[256]);
	if (auto r = stream.read(buf.get(), 255)) {
		std::cout << "read(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}

	REQUIRE(strncmp(testdata, buf.get(), 255) == 0);
}