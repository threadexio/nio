#pragma once

#include "addr.hpp"
#include "nio/base/stream.hpp"

namespace nio {
	namespace ip {
		namespace v6 {
			/**
			 * @brief An IPv6 connection stream. Do not use this directly,
			 * unless absolutely needed.
			 */
			class stream final : public base::stream {
				public:
				stream() {
				}

				/**
				 * @brief Create a new IPv6 stream on _sock.
				 *
				 * @param _sock The underlying socket file descriptor
				 * @param _p The peer address
				 */
				stream(int _sock) {
					sock = _sock;
				}

				/**
				 * @brief Get the peer address
				 *
				 * @return addr
				 */
				addr peer() {
					addr peer;
					if (getpeername(sock, peer, peer) < 0)
						NIO_THROW_ERROR(error);

					return peer;
				}
			};
		} // namespace v6
	}	  // namespace ip
} // namespace nio