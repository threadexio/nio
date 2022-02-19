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
					NIO_THROW_ERROR_CUSTOM(error, EFAULT, "Bad address");
				return _ip;
			}

			void addr::ip(const std::string& _ip) {
				switch (inet_pton(AF_INET, _ip.c_str(), &saddr.sin_addr)) {
					case 1:
						break;

					case 0:
						NIO_THROW_ERROR_CUSTOM(error, EFAULT, "Bad address");

					default:
						NIO_THROW_ERROR(error);
				}
			}
		} // namespace v4
	}	  // namespace ip
} // namespace nio