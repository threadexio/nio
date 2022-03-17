#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>

#include "nio/error.hpp"

namespace nio {

	namespace base {
		struct sock_opt {
			int level;
			int optname;
			int len;
		};

		static constexpr base::sock_opt _sopts[] = {
			{SOL_SOCKET, SO_BROADCAST, sizeof(int)},
			{SOL_SOCKET, SO_DEBUG, sizeof(int)},
			{SOL_SOCKET, SO_DONTROUTE, sizeof(int)},
			{SOL_SOCKET, SO_ERROR, sizeof(int)},
			{SOL_SOCKET, SO_KEEPALIVE, sizeof(int)},
			{SOL_SOCKET, SO_LINGER, sizeof(linger)},
			{SOL_SOCKET, SO_OOBINLINE, sizeof(int)},
			{SOL_SOCKET, SO_RCVBUF, sizeof(int)},
			{SOL_SOCKET, SO_SNDBUF, sizeof(int)},
			{SOL_SOCKET, SO_RCVLOWAT, sizeof(int)},
			{SOL_SOCKET, SO_SNDLOWAT, sizeof(int)},
			{SOL_SOCKET, SO_RCVTIMEO, sizeof(timeval)},
			{SOL_SOCKET, SO_SNDTIMEO, sizeof(timeval)},
			{SOL_SOCKET, SO_REUSEADDR, sizeof(int)},
			{SOL_SOCKET, SO_REUSEPORT, sizeof(int)},
			{SOL_SOCKET, SO_TYPE, sizeof(int)},
		};
	} // namespace base

	// Index of _sopts. Do not change the order.
	enum class option {
		BROADCAST = 0,
		DEBUG,
		DONT_ROUTE,
		ERROR,
		KEEP_ALIVE,
		LINGER,
		OOB_IN_INLINE,
		RECV_BUF,
		SEND_BUF,
		RECV_LOWAT,
		SEND_LOWAT,
		RECV_TIMEOUT,
		SEND_TIMEOUT,
		REUSE_ADDRESS,
		REUSE_PORT,
		TYPE,
	};

	constexpr int DISABLE = 0;
	constexpr int ENABLE  = 1;

	namespace base {
		class _sock {
			public:
			/**
			 * @brief Get the underlying socket file descriptor.
			 */
			inline int raw() const noexcept {
				return sock;
			}

			/**
			 * @brief Destroy the socket.
			 */
			virtual inline void close() noexcept {
				::close(sock);
			}

			virtual ~_sock() noexcept {
				close();
			}

			/**
			 * @brief Get a socket option.
			 *
			 * @param opt Option @see nio::option
			 * @param val Options value - Output parameter
			 * @return socklen_t - Size of data in val
			 */
			socklen_t get_opt(option opt, void* val) const {
				auto&	  sopt = _sopts[static_cast<int>(opt)];
				socklen_t len  = sopt.len;
				if (getsockopt(sock, sopt.level, sopt.optname, val, &len) < 0)
					NIO_THROW_ERROR(error);
				return len;
			}

			/**
			 * @brief Set a socket option.
			 *
			 * @param opt Option @see nio::option
			 * @param val
			 */
			void set_opt(option opt, const void* val) const {
				auto& sopt = _sopts[static_cast<int>(opt)];
				if (setsockopt(sock, sopt.level, sopt.optname, val, sopt.len) <
					0)
					NIO_THROW_ERROR(error);
			}

			protected:
			int sock = -1;
		};
	} // namespace base
} // namespace nio