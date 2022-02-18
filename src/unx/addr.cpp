#include "nio/unx/addr.hpp"

#include <iostream>

namespace nio {
	namespace unx {
		addr::addr(const std::string& _path) {
			memset(&saddr, 0, sizeof(saddr));

			saddr.sun_family = AF_UNIX;

			strncpy(saddr.sun_path, _path.c_str(), sizeof(saddr.sun_path) - 1);
		}

		std::string addr::path() const noexcept {
			return std::string(saddr.sun_path);
		}

		void addr::path(const std::string& _path) noexcept {
			strncpy(saddr.sun_path, _path.c_str(), sizeof(saddr.sun_path) - 1);
		}
	} // namespace unx
} // namespace nio