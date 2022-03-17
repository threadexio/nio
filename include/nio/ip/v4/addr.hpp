#pragma once

#include <netdb.h>

#include <vector>

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

				friend inline std::vector<addr> resolve(const std::string&,
														int);
			};

			/**
			 * @brief Resolve a domain name to one or more IPv4 addresses
			 *
			 * @param name Domain name
			 * @param _flags Special `getaddrinfo()` flags
			 * @return std::vector<nio::ip::v4::addr> - Returned addresses
			 */
			inline std::vector<addr> resolve(const std::string& name,
											 int				_flags = 0) {
				std::vector<addr> ret;

				addr	 a;
				addrinfo hints;
				memset(&hints, 0, sizeof(hints));
				hints.ai_family	  = a.saddr.sin_family;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_flags	  = _flags;

				addrinfo* res;
				if (getaddrinfo(name.c_str(), nullptr, &hints, &res) < 0)
					NIO_THROW_ERROR_CUSTOM(error, errno, gai_strerror(errno));

				for (addrinfo* rp = res; rp != nullptr; rp = rp->ai_next) {
					a.saddr = *(decltype(addr::saddr)*)rp->ai_addr;

					ret.push_back(a);
				}

				freeaddrinfo(res);

				return ret;
			}
		} // namespace v4
	}	  // namespace ip
} // namespace nio