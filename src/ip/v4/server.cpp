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

			Result<void*, Error> server::Bind() {
				Result<void*, Error> ret;

				sock = socket(AF_INET, SOCK_STREAM, 0);
				if (sock < 0)
					return ret.Err(errno);

				if (bind(sock, srv, srv) < 0)
					return ret.Err(errno);

				return ret.Ok(nullptr);
			}

			Result<void*, Error> server::Listen(int _queue) {
				Result<void*, Error> ret;

				if (listen(sock, _queue) < 0)
					return ret.Err(errno);

				return ret.Ok(nullptr);
			}

			Result<stream, Error> server::Accept() {
				Result<stream, Error> ret;

				addr peer;
				int	 new_stream = accept(sock, peer, peer);
				if (new_stream < 0)
					return ret.Err(errno);

				return ret.Ok(stream(new_stream, peer));
			}
		} // namespace v4
	}	  // namespace ip
} // namespace nio