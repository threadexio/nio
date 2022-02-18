#pragma once

#include "addr.hpp"
#include "nio/base/server.hpp"
#include "nio/error.hpp"
#include "stream.hpp"

namespace nio {
	namespace unx {
		/**
		 * @brief An unix server.
		 */
		class server final : public base::server<addr, stream> {
			public:
			/**
			 * @brief Create a new unix server that will listen on _server.
			 *
			 * @param _server
			 */
			server(const addr& _server);

			~server();

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
	} // namespace unx
} // namespace nio