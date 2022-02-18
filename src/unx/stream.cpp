#include "nio/unx/stream.hpp"

namespace nio {
	namespace unx {
		stream::stream(int _sock, const addr& _p) {
			_peer = _p;
			sock  = _sock;
		}
	} // namespace unx
} // namespace nio