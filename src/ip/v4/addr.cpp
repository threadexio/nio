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

			std::string addr::ip() const {
				char _ip[INET_ADDRSTRLEN] = {0};
				if (inet_ntop(AF_INET, &saddr.sin_addr, _ip, INET_ADDRSTRLEN) ==
					NULL)
					NIO_THROW_ERROR(error);
				return _ip;
			}

			void addr::ip(const std::string& _ip) {
				if (inet_pton(AF_INET, _ip.c_str(), &saddr.sin_addr) != 1)
					NIO_THROW_ERROR(error);
			}
		} // namespace v4
	}	  // namespace ip
} // namespace nio