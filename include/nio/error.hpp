#pragma once

#include <cstring>
#include <exception>
#include <string>

#define NIO_THROW_ERROR(type)			  throw type(__func__)
#define NIO_THROW_ERROR_CUSTOM(type, err) throw type(__func__, err)

namespace nio {

	class error : public std::exception {
		private:
		// Error number
		int m_errno = 0;

		// Error description
		const char* m_msg;

		// Which system call failed
		const char* m_call;

		public:
		explicit error(const char* _call, int _err = errno)
			: m_errno(_err), m_call(_call), m_msg(std::strerror(_err)) {
		}

		virtual ~error() noexcept {
		}

		/**
		 * @brief Get the reason of failure.
		 *
		 * @return const char*
		 */
		const char* what() const noexcept {
			return m_msg;
		}

		/**
		 * @brief Get which function call failed.
		 *
		 * @return const char*
		 */
		const char* which() const noexcept {
			return m_call;
		}

		/**
		 * @brief Get the error number.
		 *
		 * @return int
		 */
		int err() const noexcept {
			return m_errno;
		}
	};

	class io_error : public error {
		public:
		io_error(const char* _call) : error(_call) {
		}
	};

} // namespace nio