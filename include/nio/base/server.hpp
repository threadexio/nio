#pragma once

#include "nio/error.hpp"
#include "socket.hpp"

namespace nio {
	namespace base {

		/**
		 * @brief Base class for any server
		 *
		 * @tparam T Type of the corresponding addr class
		 * @tparam E Type of the corresponding stream class
		 */
		template <class T, class E>
		class server : public _sock {
			public:
			server() {
			}

			server(server&& other) noexcept {
				srv		   = other.srv;
				sock	   = other.sock;
				other.sock = -1;
			}

			server& operator=(server&& other) noexcept {
				if (this == &other)
					return *this;

				srv		   = other.srv;
				sock	   = other.sock;
				other.sock = -1;
				return *this;
			}

			/**
			 * @brief Create the server socket.
			 *
			 */
			virtual void create(protocol prot = protocol::STREAM) = 0;

			/**
			 * @brief Bind to the server address.
			 *
			 */
			virtual void bind() = 0;

			/**
			 * @brief Listen on the server address.
			 *
			 * @param _queue
			 */
			virtual void listen(int _queue = 5) = 0;

			/**
			 * @brief Accept a new connection from the
			 *
			 */
			virtual E accept() = 0;

			/**
			 * @brief Get the server's address.
			 *
			 * @return const T&
			 */
			const T& address() {
				return srv;
			}

			protected:
			T srv;
		};

	} // namespace base
} // namespace nio