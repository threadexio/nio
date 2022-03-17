#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#include <string>

#include "nio/base/addr.hpp"

namespace nio {
	namespace ip {
		namespace v6 {
			class addr final : public base::addr<sockaddr_in6> {
				public:
				addr() {
					memset(&saddr, 0, slen);
					saddr.sin6_family = AF_INET6;
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
					saddr.sin6_family = AF_INET6;

					ip(_ip);
					port(_port);
				}

				/**
				 * @brief Get the IP address.
				 *
				 * @return std::string
				 */
				std::string ip() const {
					char _ip[INET6_ADDRSTRLEN] = {0};
					if (inet_ntop(AF_INET6,
								  &saddr.sin6_addr,
								  _ip,
								  INET6_ADDRSTRLEN) == NULL)
						NIO_THROW_ERROR_CUSTOM(error, EFAULT, "Bad address");
					return _ip;
				}

				/**
				 * @brief Set the IP address.
				 *
				 * @param _ip
				 */
				void ip(const std::string& _ip) {
					/*
					We have to convert any uppercase hex letter to lowercase
					because apparently this doesn't work otherwise. For the
					record I have spent about an hour trying to understand why
					it didn't work.
					*/
					char		  buf[INET6_ADDRSTRLEN] = {0};
					unsigned char i						= 0;
					for (auto c : _ip) {
						if (c >= 'A' && c <= 'Z')
							c = c - ('Z' - 'z');
						buf[i] = c;
						i++;
					}

					switch (inet_pton(AF_INET6, buf, &saddr.sin6_addr)) {
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
					return ntohs(saddr.sin6_port);
				}

				/**
				 * @brief Set the port number.
				 *
				 * @param _port
				 */
				inline void port(in_port_t _port) noexcept {
					saddr.sin6_port = htons(_port);
				}

				/**
				 * @brief Convert the address to a string
				 *
				 * @return std::string
				 */
				std::string to_string() const {
					return ip() + ":" + std::to_string(port());
				}

				inline operator sockaddr_in6*() noexcept {
					return &saddr;
				}
			};
		} // namespace v6
	}	  // namespace ip
} // namespace nio