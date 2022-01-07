#include "nio/ip/v4/stream.hpp"

namespace nio {
	namespace ip {
		namespace v4 {
			stream::stream(int _sock, const addr& _p) {
				_peer = _p;
				sock  = _sock;
			}
		} // namespace v4
	}	  // namespace ip
} // namespace nio