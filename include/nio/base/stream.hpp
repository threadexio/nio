#pragma once

#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

#include "nio/error.hpp"
#include "socket.hpp"

namespace nio {
	namespace base {

		class _stream : public _sock {
			public:
			/**
			 * @brief Read from the stream _size bytes.
			 *
			 * @param _size Number of bytes to read
			 * @param _flags Special recv() flags. See `man 3 recv`
			 * @return Result<buffer, Error> - Check this for error handling
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
			 * @return Result<size_t, Error> - Check this for error handling
			 */
			size_t write(const char* _data, size_t _len, int _flags = 0) {
				ssize_t written_bytes = send(sock, _data, _len, _flags);

				if (written_bytes < 0)
					NIO_THROW_ERROR(io_error);

				return written_bytes;
			}

			inline _stream& operator<<(const char* _data) {
				write(_data, strlen(_data));
				return *this;
			}
		};

		/**
		 * @brief Base class for any stream
		 *
		 * @tparam T Type of the corresponding addr class
		 */
		template <class T>
		class stream : public _stream {
			public:
			stream() {
			}

			stream(const stream&) = delete;

			stream(stream&& other) noexcept {
				sock	   = other.sock;
				_peer	   = other._peer;
				other.sock = -1;
			}

			stream& operator=(stream&& other) noexcept {
				if (this == &other)
					return *this;

				close();
				sock	   = other.sock;
				_peer	   = other._peer;
				other.sock = -1;
				return *this;
			}

			/**
			 * @brief Get the address of the remote peer.
			 *
			 * @return const T&
			 */
			inline const T& peer() const {
				return _peer;
			};

			protected:
			T _peer;
		};
	} // namespace base
} // namespace nio
