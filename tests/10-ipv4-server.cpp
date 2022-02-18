#include <iostream>

#include "catch.hpp"
#include "nio/ip/stream.hpp"
#include "nio/ip/v4/server.hpp"

#define IP	 "127.0.0.24"
#define PORT 8888

TEST_CASE("nio::ip::v4::server tests", "[nio]") {
	try {
		nio::ip::v4::server srv(nio::ip::v4::addr(IP, PORT));

		srv.create();
		srv.set_opt(nio::option::REUSE_ADDRESS, &nio::ENABLE);
		{
			int ret;

			srv.get_opt(nio::option::REUSE_ADDRESS, &ret);
			REQUIRE(ret == 1);

			srv.get_opt(nio::option::TYPE, &ret);
			REQUIRE(ret == SOCK_STREAM);
		}

		srv.bind();
		srv.listen();

		nio::ip::v4::stream stream;
		stream = srv.accept();

		std::cout << "Peer: " << stream.peer().ip() << ":"
				  << stream.peer().port() << "\n";

		REQUIRE(stream.peer().ip() == "127.0.0.1");

		const char* testdata = "abcdefg\n\r\b\a!DSFDSW23423";

		std::unique_ptr<char[]> buf(new char[256]);
		stream.read(buf.get(), 255);

		REQUIRE(strncmp(testdata, buf.get(), 255) == 0);

		// stream.write(testdata, strlen(testdata));
		stream << testdata;
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