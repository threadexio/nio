#include "nio/ip/v6/addr.hpp"

#include <algorithm>
#include <cctype>

namespace nio {
	namespace ip {
		namespace v6 {
			addr::addr() {
				memset(&saddr, 0, slen);
				saddr.sin6_family = AF_INET6;
			}

			addr::addr(const std::string& _ip, in_port_t _port) {
				memset(&saddr, 0, slen);
				saddr.sin6_family = AF_INET6;

				ip(_ip);
				port(_port);
			}

			std::string addr::ip() const {
				char _ip[INET6_ADDRSTRLEN] = {0};
				if (inet_ntop(
						AF_INET6, &saddr.sin6_addr, _ip, INET6_ADDRSTRLEN) ==
					NULL)
					NIO_THROW_ERROR_CUSTOM(error, EFAULT, "Bad address");
				return _ip;
			}

			void addr::ip(const std::string& _ip) {
				/*
				We have to convert any uppercase hex letter to lowercase because
				apparently this doesn't work otherwise. For the record I have
				spent about an hour trying to understand why it didn't work.
				*/
				char		  buf[INET6_ADDRSTRLEN];
				unsigned char i = 0;
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
						NIO_THROW_ERROR_CUSTOM(error, EFAULT, "Bad address");

					default:
						NIO_THROW_ERROR(error);
				}
			}
		} // namespace v6
	}	  // namespace ip
} // namespace nio