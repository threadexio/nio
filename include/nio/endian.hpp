#pragma once

#include <byteswap.h>
#include <stdint.h>

namespace nio {
	namespace endian {
		inline uint16_t byteswap16(uint16_t x) {
			return bswap_16(x);
		}

		inline uint32_t byteswap32(uint32_t x) {
			return bswap_32(x);
		}

		inline uint64_t byteswap64(uint64_t x) {
			return bswap_64(x);
		}

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

		inline uint16_t tobe16(uint16_t x) {
			return x;
		}
		inline uint32_t tobe32(uint32_t x) {
			return x;
		}
		inline uint64_t tobe64(uint64_t x) {
			return x;
		}

		inline uint16_t tole16(uint16_t x) {
			return byteswap16(x)
		}
		inline uint32_t tole32(uint32_t x) {
			return byteswap32(x)
		}
		inline uint64_t tole64(uint64_t x) {
			return byteswap64(x)
		}

#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

		inline uint16_t tobe16(uint16_t x) {
			return byteswap16(x);
		}
		inline uint32_t tobe32(uint32_t x) {
			return byteswap32(x);
		}
		inline uint64_t tobe64(uint64_t x) {
			return byteswap64(x);
		}

		inline uint16_t tole16(uint16_t x) {
			return x;
		}
		inline uint32_t tole32(uint32_t x) {
			return x;
		}
		inline uint64_t tole64(uint64_t x) {
			return x;
		}

#else
#error "System is not little or big endian"
#endif

		inline uint16_t tonet16(uint16_t x) {
			return tobe16(x);
		}
		inline uint32_t tonet32(uint32_t x) {
			return tobe32(x);
		}
		inline uint64_t tonet64(uint64_t x) {
			return tobe64(x);
		}

		inline uint16_t tohost16(uint16_t x) {
			return tole16(x);
		}
		inline uint32_t tohost32(uint32_t x) {
			return tole32(x);
		}
		inline uint64_t tohost64(uint64_t x) {
			return tole64(x);
		}

	} // namespace endian
} // namespace nio
