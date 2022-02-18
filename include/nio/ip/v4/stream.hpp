#pragma once

#include "addr.hpp"
#include "nio/base/stream.hpp"

namespace nio {
	namespace ip {
		namespace v4 {
			/**
			 * @brief An IPv4 connection stream. Do not use this directly,
			 * unless absolutely needed.
			 */
			class stream final : public base::stream<addr> {
				public:
				/**
				 * @brief Create a new IPv4 stream on _sock.
				 *
				 * @param _sock The underlying socket file descriptor
				 * @param _p The peer address
				 */
				stream(int _sock, const addr& _p);
			};
		} // namespace v4
	}	  // namespace ip
} // namespace nio