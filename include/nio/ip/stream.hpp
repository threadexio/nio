#pragma once

#include "nio/base/stream.hpp"

namespace nio {
	namespace ip {

		/**
		 * @brief A type representing all IP streams.
		 *
		 */
		class stream : public base::stream<sockaddr> {};

	} // namespace ip
} // namespace nio