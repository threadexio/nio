#pragma once

#include "addr.hpp"
#include "nio/base/client.hpp"
#include "nio/error.hpp"
#include "stream.hpp"

namespace nio {
	namespace ip {
		namespace v4 {
			/**
			 * @brief An IPv4 client.
			 */
			class client final : public base::client<addr, stream> {
				public:
				/**
				 * @brief Create a new IPv4 client which will connect to
				 * _remote.
				 *
				 * @param _remote
				 */
				client(const addr& _remote);

				/**
				 * @brief Create the client socket.
				 *
				 * @return Result<stream, Error> - Check this for error handling
				 */
				Result<void*, Error> Create();

				/**
				 * @brief Connect to the endpoint specified.
				 *
				 * @return Result<stream, Error> - Check this for error handling
				 */
				Result<stream, Error> Connect();
			};
		} // namespace v4
	}	  // namespace ip
} // namespace nio