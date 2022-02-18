#pragma once

#include "addr.hpp"
#include "nio/base/server.hpp"
#include "nio/error.hpp"
#include "stream.hpp"

namespace nio {
	namespace ip {
		namespace v6 {
			/**
			 * @brief An IPv4 server.
			 */
			class server final : public base::server<addr, stream> {
				public:
				/**
				 * @brief Create a new IPv4 server that will listen on _server.
				 *
				 * @param _server
				 */
				server(const addr& _server);

				/**
				 * @brief Create the server socket. Should be called after the
				 * constructor.
				 *
				 */
				void create(protocol prot = protocol::STREAM);

				/**
				 * @brief Bind to the specified address and get ready to listen.
				 *
				 */
				void bind();

				/**
				 * @brief Listen on the specified address and get ready to
				 * accept incoming connections.
				 *
				 * @param _queue
				 */
				void listen(int _queue = 5);

				/**
				 * @brief Accept an incoming connection.
				 *
				 * @return stream - The new connection stream
				 */
				stream accept();
			};
		} // namespace v6
	}	  // namespace ip
} // namespace nio