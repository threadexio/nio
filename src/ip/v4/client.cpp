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

			Result<stream, Error> client::Connect() {
				Result<stream, Error> ret;

				sock = socket(AF_INET, SOCK_STREAM, 0);

				addr peer;

				if (connect(sock, remote, remote) < 0)
					return ret.Err(errno);

				if (getpeername(sock, peer, peer) < 0)
					return ret.Err(errno);

				return ret.Ok(stream(sock, peer));
			}
		} // namespace v4
	}	  // namespace ip
} // namespace nio
