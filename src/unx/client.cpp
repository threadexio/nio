#include "nio/unx/client.hpp"

#include <sys/socket.h>

#include <cerrno>

#include "nio/error.hpp"
#include "nio/unx/addr.hpp"
#include "nio/unx/stream.hpp"

namespace nio {
	namespace unx {
		client::client(const addr& _remote) {
			remote = _remote;
		}

		void client::create(protocol prot) {
			sock = socket(AF_UNIX, static_cast<int>(prot), 0);
			if (sock < 0)
				NIO_THROW_ERROR(error);
		}

		stream client::connect() {
			addr peer;

			if (::connect(sock, remote, remote) < 0)
				NIO_THROW_ERROR(error);

			peer = remote;

			return stream(sock, peer);
		}
	} // namespace unx
} // namespace nio
