#pragma once

#include "addr.hpp"
#include "nio/base/server.hpp"
#include "nio/error.hpp"
#include "stream.hpp"

namespace nio {
	namespace ip {
		namespace v4 {
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
				 * @return Result<void*, Error> - Check this for error handling
				 */
				Result<void*, Error> Create();

				/**
				 * @brief Bind to the specified address and get ready to listen.
				 *
				 * @return Result<void*, Error> - Check this for error handling
				 */
				Result<void*, Error> Bind();

				/**
				 * @brief Listen on the specified address and get ready to
				 * accept incoming connections.
				 *
				 * @param _queue
				 * @return Result<void*, Error> - Check this for error handling
				 */
				Result<void*, Error> Listen(int _queue = 5);

				/**
				 * @brief Accept an incoming connection.
				 *
				 * @return Result<stream, Error> - Check this for error handling
				 */
				Result<stream, Error> Accept();
			};
		} // namespace v4
	}	  // namespace ip
} // namespace nio