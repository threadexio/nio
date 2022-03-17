#pragma once

#include "addr.hpp"
#include "nio/base/client.hpp"
#include "nio/error.hpp"
#include "stream.hpp"

namespace nio {
	namespace ip {
		namespace v6 {
			/**
			 * @brief An IPv6 client.
			 */
			class client final : public base::client<addr, stream> {
				public:
				/**
				 * @brief Create a new IPv6 client which will connect to
				 * _remote.
				 *
				 * @param _remote
				 */
				client(const addr& _remote) {
					remote = _remote;
				}

				/**
				 * @brief Create the client socket.
				 *
				 */
				void create(protocol prot = protocol::STREAM) {
					sock = socket(AF_INET6, static_cast<int>(prot), 0);
					if (sock < 0)
						NIO_THROW_ERROR(error);
				}

				/**
				 * @brief Connect to the endpoint specified.
				 *
				 * @return stream - The new connection stream
				 */
				stream connect() {
					addr peer;

					if (::connect(sock, remote, remote) < 0)
						NIO_THROW_ERROR(error);

					if (getpeername(sock, peer, peer) < 0)
						NIO_THROW_ERROR(error);

					return stream(sock, peer);
				}
			};
		} // namespace v6
	}	  // namespace ip
} // namespace nio