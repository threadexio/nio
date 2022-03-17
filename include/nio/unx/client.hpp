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
			void create(protocol prot = protocol::STREAM) {
				sock = socket(AF_UNIX, static_cast<int>(prot), 0);
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

				peer = remote;

				return stream(sock, peer);
			}
		};
	} // namespace unx
} // namespace nio