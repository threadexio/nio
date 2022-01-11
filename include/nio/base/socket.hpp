#pragma once

#include <unistd.h>

namespace nio {
	namespace base {
		class _sock {
			public:
			/**
			 * @brief Get the underlying socket file descriptor.
			 */
			inline int raw() const {
				return sock;
			}

			/**
			 * @brief Cleanup the socket.
			 */
			virtual inline void shutdown() {
				close(sock);
			}

			virtual ~_sock() {
				shutdown();
			}

			protected:
			int sock = -1;
		};
	} // namespace base
} // namespace nio