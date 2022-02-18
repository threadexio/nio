#include "nio/ip/v4/client.hpp"

#include <sys/socket.h>

#include <cerrno>

#include "nio/error.hpp"
#include "nio/ip/v4/addr.hpp"
#include "nio/ip/v4/stream.hpp"

namespace nio {
	namespace ip {
		namespace v4 {
			client::client(const addr& _remote) {
				remote = _remote;
			}

			void client::create(protocol prot) {
				sock = socket(AF_INET, static_cast<int>(prot), 0);
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
		} // namespace v4
	}	  // namespace ip
} // namespace nio
