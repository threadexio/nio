#include <iostream>

#include "catch.hpp"
#include "nio/stream.hpp"
#include "nio/unx/server.hpp"

#define PATH "/tmp/test.sock"

TEST_CASE("nio::unx::server tests", "[nio]") {
	try {
		nio::unx::server srv(nio::unx::addr(PATH));

		srv.create();

		srv.bind();
		srv.listen();

		nio::unx::stream stream;
		stream = srv.accept();

		std::cout << "Peer: " << srv.address().path() << "\n";

		REQUIRE(srv.address().path() == PATH);

		const char* testdata = "abcdefg\n\r\b\a!DSFDSW23423";

		std::unique_ptr<char[]> buf(new char[256]);
		stream.read(buf.get(), 255);

		REQUIRE(strncmp(testdata, buf.get(), 255) == 0);

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