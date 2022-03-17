#pragma once

#include "addr.hpp"
#include "nio/base/server.hpp"
#include "nio/error.hpp"
#include "stream.hpp"

namespace nio {
	namespace ip {
		namespace v6 {
			/**
			 * @brief An IPv6 server.
			 */
			class server final : public base::server<addr, stream> {
				public:
				/**
				 * @brief Create a new IPv6 server that will listen on _server.
				 *
				 * @param _server
				 */
				server(const addr& _server) {
					srv = _server;
				}

				/**
				 * @brief Create the server socket. Should be called after the
				 * constructor.
				 *
				 */
				void create(protocol prot = protocol::STREAM) {
					sock = socket(AF_INET6, static_cast<int>(prot), 0);
					if (sock < 0)
						NIO_THROW_ERROR(error);
				}

				/**
				 * @brief Bind to the specified address and get ready to listen.
				 *
				 */
				void bind() {
					if (::bind(sock, srv, srv) < 0)
						NIO_THROW_ERROR(error);
				}

				/**
				 * @brief Listen on the specified address and get ready to
				 * accept incoming connections.
				 *
				 * @param _queue
				 */
				void listen(int _queue = 5) {
					if (::listen(sock, _queue) < 0)
						NIO_THROW_ERROR(error);
				}

				/**
				 * @brief Accept an incoming connection.
				 *
				 * @return stream - The new connection stream
				 */
				stream accept() {
					addr peer;
					int	 new_stream = ::accept(sock, peer, peer);
					if (new_stream < 0)
						NIO_THROW_ERROR(error);

					return stream(new_stream);
				}
			};
		} // namespace v6
	}	  // namespace ip
} // namespace nio