#pragma once

#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

#include "nio/error.hpp"
#include "socket.hpp"

namespace nio {
	namespace base {

		class stream : public _sock {
			public:
			stream() {
			}

			stream(const stream&) = delete;

			stream(stream&& other) noexcept {
				close();
				sock	   = other.sock;
				other.sock = -1;
			}

			stream& operator=(stream&& other) noexcept {
				if (this == &other)
					return *this;

				close();
				sock	   = other.sock;
				other.sock = -1;
				return *this;
			}

			/**
			 * @brief Read from the stream _size bytes.
			 *
			 * @param _size Number of bytes to read
			 * @param _flags Special recv() flags. See `man 3 recv`
			 * @return size_t - Number of bytes read
			 */
			size_t read(char* _buf, size_t _size, int _flags = 0) const {
				int read_bytes = recv(sock, _buf, _size, _flags);
				if (read_bytes < 0)
					NIO_THROW_ERROR(io_error);

				return read_bytes;
			}

			/**
			 * @brief Write _data to the stream.
			 *
			 * @param _data The data to write
			 * @param _len Size of the data (in bytes), 0 means the whole buffer
			 * @param _flags Special send() flags. See `man 3 send`
			 * @return size_t - Number of bytes written
			 */
			size_t write(const char* _data, size_t _len, int _flags = 0) {
				ssize_t written_bytes = send(sock, _data, _len, _flags);

				if (written_bytes < 0)
					NIO_THROW_ERROR(io_error);

				return written_bytes;
			}

			inline stream& operator<<(const char* _data) {
				write(_data, strlen(_data));
				return *this;
			}
		};
	} // namespace base
} // namespace nio
