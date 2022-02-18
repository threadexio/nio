#include "nio/ip/v6/stream.hpp"

namespace nio {
	namespace ip {
		namespace v6 {
			stream::stream(int _sock, const addr& _p) {
				_peer = _p;
				sock  = _sock;
			}
		} // namespace v6
	}	  // namespace ip
} // namespace nio