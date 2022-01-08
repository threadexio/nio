#pragma once

#include <unistd.h>

#include <iostream>

namespace nio {
	namespace base {
		class _sock {
			public:
			/**
			 * @brief Get the underlying socket file descriptor.
			 */
			int raw() const {
				return sock;
			}

			/**
			 * @brief Cleanup the socket.
			 */
			virtual void shutdown() {
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