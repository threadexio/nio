#include "nio/ip/v4/server.hpp"

#include <sys/socket.h>

#include "nio/error.hpp"
#include "nio/ip/v4/addr.hpp"
#include "nio/ip/v4/stream.hpp"

namespace nio {
	namespace ip {
		namespace v4 {
			server::server(const addr& _srv) {
				srv = _srv;
			}

			void server::create(protocol prot) {
				sock = socket(AF_INET, static_cast<int>(prot), 0);
				if (sock < 0)
					NIO_THROW_ERROR(error);
			}

			void server::bind() {
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
		} // namespace v4
	}	  // namespace ip
} // namespace nio