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
			client(const addr& _remote);

			/**
			 * @brief Create the client socket.
			 *
			 */
			void create(protocol prot = protocol::STREAM);

			/**
			 * @brief Connect to the endpoint specified.
			 *
			 * @return stream - The new connection stream
			 */
			stream connect();
		};
	} // namespace unx
} // namespace nio