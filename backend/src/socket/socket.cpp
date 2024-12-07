#include <memory>
#include <netinet/in.h> // For sockaddr_in
#include <sys/socket.h> // For socket functions
#include <sys/types.h>
#include <unistd.h> // For read

#include "client.hpp"
#include "exceptions.hpp"
#include "pool.hpp"
#include "socket.hpp"

s_socket::s_socket() {
  try {
    start();
    alive = true;
  } catch (socket_exception se) {
    alive = false;
    throw;
  }
}

void s_socket::start() {
  // Create a socket (IPv4, TCP)
  server = socket(AF_INET, SOCK_STREAM, 0);
  if (server == -1)
    throw socket_exception("Failed to create socket.");

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(9999);

  int enable = 1;

  if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    throw socket_exception("SO_REUSEADDR not available.");

  if (bind(server, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    throw socket_exception("Failed to bind to port 9999.");

  if (listen(server, 10) < 0)
    throw socket_exception("Failed to listen on socket.");
}

int s_socket::serve() {
  int clients = 0;
  thread_pool pool(4);

  while (true) {
    int client_fd = accept_connection();
    std::shared_ptr<client> cl =
        std::make_shared<client>(client_fd, (char *)"");
    //    pool.add_task(cl);
  }

  return clients;
}

int s_socket::accept_connection() {
  auto addrlen = sizeof(sockaddr);
  int client =
      accept(server, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

  if (client < 0) {
    throw socket_exception("Failed to grab connection.");
  }

  return client;
}

bool s_socket::halt() {
  // Close the connections
  shutdown(server, SHUT_WR);

  return close(server) == 0;
}

bool s_socket::is_active() { return alive; }
