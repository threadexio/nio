#include "nio/ip/v4/addr.hpp"

namespace nio {
	namespace ip {
		namespace v4 {
			addr::addr() {
				memset(&saddr, 0, slen);
				saddr.sin_family = AF_INET;
			}

			addr::addr(const std::string& _ip, in_port_t _port) {
				memset(&saddr, 0, slen);
				saddr.sin_family = AF_INET;

				ip(_ip);
				port(_port);
			}
		} // namespace v4
	}	  // namespace ip
} // namespace nio