#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#include <string>

#include "nio/base/addr.hpp"

namespace nio {
	namespace ip {
		namespace v4 {
			class addr final : public base::addr<sockaddr_in> {
				public:
				/**
				 * @brief Create a new addr object the represents the endpoint
				 * _ip:_port
				 *
				 * @param _ip
				 * @param _port
				 */
				addr(const std::string& _ip, in_port_t _port);

				/**
				 * @brief Get the IP address.
				 *
				 * @return std::string
				 */
				std::string ip() const;

				/**
				 * @brief Set the IP address.
				 *
				 * @param _ip
				 */
				void ip(const std::string& _ip);

				/**
				 * @brief Get the port number.
				 *
				 * @return in_port_t
				 */
				inline in_port_t port() const noexcept {
					return ntohs(saddr.sin_port);
				}

				/**
				 * @brief Set the port number.
				 *
				 * @param _port
				 */
				inline void port(in_port_t _port) noexcept {
					saddr.sin_port = htons(_port);
				}

				inline operator sockaddr_in*() noexcept {
					return &saddr;
				}
			};
		} // namespace v4
	}	  // namespace ip
} // namespace nio