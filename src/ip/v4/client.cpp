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

			Result<void*, Error> client::Create(PROTOCOL prot) {
				Result<void*, Error> ret;

				sock = socket(AF_INET, static_cast<int>(prot), 0);
				if (sock < 0)
					return std::move(ret.Err(errno));

				return std::move(ret.Ok(nullptr));
			}

			Result<stream, Error> client::Connect() {
				Result<stream, Error> ret;
				addr				  peer;

				if (connect(sock, remote, remote) < 0)
					return std::move(ret.Err(errno));

				if (getpeername(sock, peer, peer) < 0)
					return std::move(ret.Err(errno));

				return std::move(ret.Ok(stream(sock, peer)));
			}
		} // namespace v4
	}	  // namespace ip
} // namespace nio
