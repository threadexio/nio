#include <iostream>

#include "catch.hpp"
#include "nio/ip/v4/server.hpp"

#define IP	 "127.0.0.24"
#define PORT 8888

static nio::ip::v4::server srv(nio::ip::v4::addr(IP, PORT));

TEST_CASE("nio::ip::v4::server tests", "[nio]") {
	if (auto r = srv.Create()) {
		std::cout << "Create(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}

	if (auto r = srv.set_opt(nio::SOPT::REUSE_ADDRESS, &nio::ENABLE)) {
		std::cout << "set_opt(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}

	{
		int ret;
		if (auto r = srv.get_opt(nio::SOPT::REUSE_ADDRESS, &ret)) {
			std::cout << "get_opt(REUSE_ADDRESS): " << r.Err().msg << "\n";
			REQUIRE(false);
		}
		REQUIRE(ret == 1);

		if (auto r = srv.get_opt(nio::SOPT::TYPE, &ret)) {
			std::cout << "get_opt(TYPE): " << r.Err().msg << "\n";
			REQUIRE(false);
		}
		REQUIRE(ret == SOCK_STREAM);
	}

	if (auto r = srv.Bind()) {
		std::cout << "Bind(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}

	if (auto r = srv.Listen()) {
		std::cout << "Listen(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}

	nio::ip::v4::stream stream;
	if (auto r = srv.Accept()) {
		std::cout << "Accept(): " << r.Err().msg << "\n";
	} else {
		stream = r.Ok();
	}

	std::cout << "Peer: " << stream.peer().ip() << ":" << stream.peer().port()
			  << "\n";

	REQUIRE(stream.peer().ip() == "127.0.0.1");

	const char* testdata = "abcdefg\n\r\b\a!DSFDSW23423";

	std::unique_ptr<char[]> buf(new char[256]);
	if (auto r = stream.read(buf.get(), 255)) {
		std::cout << "read(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}

	REQUIRE(strncmp(testdata, buf.get(), 255) == 0);

	if (auto r = stream.write(testdata, strlen(testdata))) {
		std::cout << "write(): " << r.Err().msg << "\n";
		REQUIRE(false);
	}
}