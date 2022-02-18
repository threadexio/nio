#include "nio/ip/v6/client.hpp"

#include <sys/socket.h>

#include <cerrno>

#include "nio/error.hpp"
#include "nio/ip/v6/addr.hpp"
#include "nio/ip/v6/stream.hpp"

namespace nio {
	namespace ip {
		namespace v6 {
			client::client(const addr& _remote) {
				remote = _remote;
			}

			void client::create(protocol prot) {
				sock = socket(AF_INET6, static_cast<int>(prot), 0);
				if (sock < 0)
					NIO_THROW_ERROR(error);
			}

			stream client::connect() {
				addr peer;

				if (::connect(sock, remote, remote) < 0)
					NIO_THROW_ERROR(error);

				if (getpeername(sock, peer, peer) < 0)
					NIO_THROW_ERROR(error);

				return stream(sock, peer);
			}
		} // namespace v6
	}	  // namespace ip
} // namespace nio
