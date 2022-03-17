#pragma once

#include <sys/socket.h>
#include <sys/un.h>

#include <cstring>
#include <string>

#include "nio/base/addr.hpp"

namespace nio {
	namespace unx {
		class addr final : public base::addr<sockaddr_un> {
			public:
			addr() {
				memset(&saddr, 0, slen);
				saddr.sun_family = AF_UNIX;
			}

			/**
			 * @brief Create a new UNIX socket address.
			 *
			 * @param _path Socket path
			 */
			addr(const std::string& _path) {
				memset(&saddr, 0, sizeof(saddr));

				saddr.sun_family = AF_UNIX;

				strncpy(
					saddr.sun_path, _path.c_str(), sizeof(saddr.sun_path) - 1);
			}

			/**
			 * @brief Get the path.
			 *
			 * @return std::string
			 */
			std::string path() const noexcept {
				return std::string(saddr.sun_path);
			}

			/**
			 * @brief Set the path.
			 *
			 * @param _path
			 */
			void path(const std::string& _path) noexcept {
				strncpy(
					saddr.sun_path, _path.c_str(), sizeof(saddr.sun_path) - 1);
			}

			/**
			 * @brief Convert the address to a string
			 *
			 * @return std::string
			 */
			std::string to_string() const {
				return path();
			}
		};
	} // namespace unx
} // namespace nio