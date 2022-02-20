#include "nio/unx/server.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include "nio/error.hpp"
#include "nio/unx/addr.hpp"
#include "nio/unx/stream.hpp"

namespace nio {
	namespace unx {
		server::server(const addr& _srv) {
			srv = _srv;
		}

		server::~server() {
			/*
			Linux	2021-03-22	UNIX(7)
			Binding to a socket with a filename creates a socket in the
			filesystem that must be deleted by the caller when it is no longer
			needed (using unlink(2)).  The usual UNIX  close- behind semantics
			apply; the socket can be unlinked at any time and will be finally
			removed from the filesystem when the last reference to it is closed.

			This means we don't have to write some kind of hook into
			base::_sock's destructor to unlink after close.
			*/
			unlink(srv.path().c_str());
		}

		void server::create(protocol prot) {
			sock = socket(AF_UNIX, static_cast<int>(prot), 0);
			if (sock < 0)
				NIO_THROW_ERROR(error);
		}

		void server::bind() {
			unlink(srv.path().c_str());
			if (::bind(sock, srv, srv) < 0)
				NIO_THROW_ERROR(error);
		}

		void server::listen(int _queue) {
			if (::listen(sock, _queue) < 0)
				NIO_THROW_ERROR(error);
		}

		stream server::accept() {
			addr peer;
			int	 new_stream = ::accept(sock, peer, peer);
			if (new_stream < 0)
				NIO_THROW_ERROR(error);

			return stream(new_stream, peer);
		}
	} // namespace unx
} // namespace nio