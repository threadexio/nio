#pragma once

#include "nio/error.hpp"
#include "socket.hpp"

namespace nio {
	namespace base {

		/**
		 * @brief Base class for any client
		 *
		 * @tparam T Type of the corresponding addr class
		 * @tparam E Type of the corresponding stream class
		 */
		template <class T, class E>
		class client : public _sock {
			public:
			client() {
			}

			client(client&& other) noexcept {
				remote	   = other.remote;
				sock	   = other.sock;
				other.sock = -1;
			}

			client& operator=(client&& other) noexcept {
				if (this == &other)
					return *this;

				remote	   = other.remote;
				sock	   = other.sock;
				other.sock = -1;
			}

			/**
			 * @brief Create the client socket.
			 *
			 * @return Result<E, Error> - Check this for error handling
			 */
			virtual Result<void*, Error> Create() = 0;

			/**
			 * @brief Connect to a remote endpoint.
			 *
			 * @return Result<E, Error> - Check this for error handling
			 */
			virtual Result<E, Error> Connect() = 0;

			protected:
			T remote;
		};

	} // namespace base
} // namespace nio