#pragma once

#include "addr.hpp"
#include "nio/base/server.hpp"
#include "nio/error.hpp"
#include "stream.hpp"

namespace nio {
	namespace unx {
		/**
		 * @brief An unix server.
		 */
		class server final : public base::server<addr, stream> {
			public:
			/**
			 * @brief Create a new unix server that will listen on _server.
			 *
			 * @param _server
			 */
			server(const addr& _server) {
				srv = _server;
			}

			~server() {
				/*
				Linux	2021-03-22	UNIX(7)
				Binding to a socket with a filename creates a socket in the
				filesystem that must be deleted by the caller when it is no
				longer needed (using unlink(2)).  The usual UNIX  close- behind
				semantics apply; the socket can be unlinked at any time and will
				be finally removed from the filesystem when the last reference
				to it is closed. This means we don't have to write some kind of
				hook into base::_sock's destructor to unlink after close.
				*/
				unlink(srv.path().c_str());
			}

			/**
			 * @brief Create the server socket. Should be called after the
			 * constructor.
			 *
			 */
			void create(protocol prot = protocol::STREAM) {
				sock = socket(AF_UNIX, static_cast<int>(prot), 0);
				if (sock < 0)
					NIO_THROW_ERROR(error);
			}

			/**
			 * @brief Bind to the specified address and get ready to listen.
			 *
			 */
			void bind() {
				unlink(srv.path().c_str());
				if (::bind(sock, srv, srv) < 0)
					NIO_THROW_ERROR(error);
			}

			/**
			 * @brief Listen on the specified address and get ready to
			 * accept incoming connections.
			 *
			 * @param _queue
			 */
			void listen(int _queue = 5) {
				if (::listen(sock, _queue) < 0)
					NIO_THROW_ERROR(error);
			}

			/**
			 * @brief Accept an incoming connection.
			 *
			 * @return stream - The new connection stream
			 */
			stream accept() {
				addr peer;
				int	 new_stream = ::accept(sock, peer, peer);
				if (new_stream < 0)
					NIO_THROW_ERROR(error);

				return stream(new_stream);
			}
		};
	} // namespace unx
} // namespace nio