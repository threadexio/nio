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
			}

			/**
			 * @brief Create a new UNIX socket address.
			 *
			 * @param _path Socket path
			 */
			addr(const std::string& _path);

			/**
			 * @brief Get the path.
			 *
			 * @return std::string
			 */
			std::string path() const noexcept;

			/**
			 * @brief Set the path.
			 *
			 * @param _path
			 */
			void path(const std::string& _path) noexcept;
		};
	} // namespace unx
} // namespace nio