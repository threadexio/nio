#pragma once

#include <netinet/in.h>

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
			/**
			 * @brief Get the address in a human readable way.
			 *
			 * @return std::string
			 */
			virtual std::string ip() const = 0;

			/**
			 * @brief Set the address from a string.
			 *
			 * @param _ip
			 */
			virtual void ip(const std::string& _ip) = 0;

			/**
			 * @brief Get the port number.
			 *
			 * @return in_port_t
			 */
			virtual in_port_t port() const noexcept = 0;

			/**
			 * @brief Set the port number.
			 *
			 * @param _port
			 */
			virtual void port(in_port_t _port) noexcept = 0;

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
