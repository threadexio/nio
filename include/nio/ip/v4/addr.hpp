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
				addr() {
					memset(&saddr, 0, slen);
					saddr.sin_family = AF_INET;
				}

				/**
				 * @brief Create a new addr object the represents the endpoint
				 * _ip:_port
				 *
				 * @param _ip
				 * @param _port
				 */
				addr(const std::string& _ip, in_port_t _port) {
					memset(&saddr, 0, slen);
					saddr.sin_family = AF_INET;

					ip(_ip);
					port(_port);
				}

				/**
				 * @brief Get the IP address.
				 *
				 * @return std::string
				 */
				std::string ip() const {
					char _ip[INET_ADDRSTRLEN] = {0};
					if (inet_ntop(
							AF_INET, &saddr.sin_addr, _ip, INET_ADDRSTRLEN) ==
						NULL)
						NIO_THROW_ERROR_CUSTOM(error, EFAULT, "Bad address");
					return _ip;
				}

				/**
				 * @brief Set the IP address.
				 *
				 * @param _ip
				 */
				void ip(const std::string& _ip) {
					switch (inet_pton(AF_INET, _ip.c_str(), &saddr.sin_addr)) {
						case 1:
							break;

						case 0:
							NIO_THROW_ERROR_CUSTOM(
								error, EFAULT, "Bad address");

						default:
							NIO_THROW_ERROR(error);
					}
				}

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

				/**
				 * @brief Convert the address to a string
				 *
				 * @return std::string
				 */
				std::string to_string() const {
					return ip() + ":" + std::to_string(port());
				}

				inline operator sockaddr_in*() noexcept {
					return &saddr;
				}
			};
		} // namespace v4
	}	  // namespace ip
} // namespace nio