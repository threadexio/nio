#pragma once

#include "addr.hpp"
#include "nio/base/client.hpp"
#include "nio/error.hpp"
#include "stream.hpp"

namespace nio {
	namespace unx {
		/**
		 * @brief An unix client.
		 */
		class client final : public base::client<addr, stream> {
			public:
			/**
			 * @brief Create a new unix client which will connect to
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
			void create() {
				sock = socket(AF_UNIX, SOCK_STREAM, 0);
				if (sock < 0)
					NIO_THROW_ERROR(error);
			}

			/**
			 * @brief Connect to the endpoint specified.
			 *
			 * @return stream - The new connection stream
			 */
			stream connect() {
				if (::connect(sock, remote, remote) < 0)
					NIO_THROW_ERROR(error);

				return stream(sock);
			}
		};
	} // namespace unx
} // namespace nio