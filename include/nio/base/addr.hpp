#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <cstring>
#include <string>

#include "nio/error.hpp"

namespace nio {
	namespace base {

		/**
		 * @brief Base class for any address.
		 *
		 * @tparam T Type of the underlying sockaddr C struct
		 */
		template <class T>
		class addr {
			public:
			virtual std::string to_string() const = 0;

			inline operator socklen_t() {
				return slen;
			}

			inline operator socklen_t*() noexcept {
				return &slen;
			}

			inline operator sockaddr*() noexcept {
				return (sockaddr*)&saddr;
			}

			protected:
			T		  saddr;
			socklen_t slen = sizeof(T);
		};
	} // namespace base
} // namespace nio
