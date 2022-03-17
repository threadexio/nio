#pragma once

#include "addr.hpp"
#include "nio/base/stream.hpp"

namespace nio {
	namespace unx {
		/**
		 * @brief An unix connection stream. Do not use this directly,
		 * unless absolutely needed.
		 */
		class stream final : public base::stream {
			public:
			stream() {
			}

			/**
			 * @brief Create a new unix stream on _sock.
			 *
			 * @param _sock The underlying socket file descriptor
			 * @param _p The peer address
			 */
			stream(int _sock) {
				sock = _sock;
			}
		};
	} // namespace unx
} // namespace nio