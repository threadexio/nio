#pragma once

#include <sys/socket.h>
#include <unistd.h>

#include "nio/buffer.hpp"
#include "nio/error.hpp"
#include "socket.hpp"

namespace nio {
	namespace base {

		/**
		 * @brief Base class for any stream
		 *
		 * @tparam T Type of the corresponding addr class
		 */
		template <class T>
		class stream : public _sock {
			public:
			/**
			 * @brief Read from the stream _size bytes.
			 *
			 * @param _size Number of bytes to read
			 * @param _flags Special recv() flags. See `man 3 recv`
			 * @return Result<buffer, Error> - Check this for error handling
			 */
			Result<buffer, Error> read(size_t _size, int _flags = 0) {
				Result<buffer, Error> ret;

				buffer buf(_size);

				int read_bytes = recv(sock, buf.data(), _size, _flags);
				if (read_bytes < 0)
					return ret.Err(errno);

				buf.resize(read_bytes);

				return ret.Ok(buf);
			}

			/**
			 * @brief Write _data to the stream.
			 *
			 * @param _data The data to write
			 * @param _len Size of the data (in bytes), 0 means the whole buffer
			 * @param _flags Special send() flags. See `man 3 send`
			 * @return Result<size_t, Error> - Check this for error handling
			 */
			Result<size_t, Error> write(const buffer& _data,
										size_t		  _len	 = 0,
										int			  _flags = 0) {
				Result<size_t, Error> ret;

				ssize_t written_bytes =
					send(sock,
						 _data.data(),
						 (_len == 0) ? _data.length() : _len,
						 _flags);

				if (written_bytes < 0)
					return ret.Err(errno);

				return ret.Ok(written_bytes);
			}

			/**
			 * @brief Get the address of the remote peer.
			 *
			 * @return const T&
			 */
			const T& peer() const {
				return _peer;
			};

			protected:
			T _peer;
		};
	} // namespace base
} // namespace nio
