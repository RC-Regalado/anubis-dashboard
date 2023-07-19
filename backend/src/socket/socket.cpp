#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <format>
#include <fstream>
#include <netinet/in.h> // For sockaddr_in
#include <string>
#include <sys/socket.h> // For socket functions
#include <sys/types.h>
#include <thread>
#include <unistd.h> // For read

#include "exceptions.hpp"
#include "socket.hpp"

bool strcontains(const std::string &str, const char *substr) {
  return str.find(substr) != std::string::npos;
}

s_socket::s_socket() {
  try {
    start();
    alive = true;
  } catch (socket_exception se) {
    throw se;
    alive = false;
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

int s_socket::serve(){
  int clients = 0;
  while (true) {
    int client = accept_connection();
    std::thread t(&s_socket::handle_connection, this, client);

    t.detach();

    if (clients++ > 3) break;
  }

  return clients;
}

void s_socket::wait(int client_socket) {
  receive(client_socket);
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

std::string s_socket::receive(int client_socket) {
  char buffer[256];
  int n = 1;
  char *end = nullptr;
  std::string headers_data, request;

  unsigned short int i = 0;

  size_t pos = 0;
  const char *delimiter = "\r\n";
  int delimiter_len = strlen(delimiter);

  while (n > 0) {
    n = read(client_socket, buffer, 255);

    if (n < 0)
      throw socket_exception("Failed reading from socket.");
    if (n == 0)
      throw socket_exception("peer shutted down");

    headers_data += std::string(buffer, n);
    if (strcontains(headers_data, "\r\n\r\n") || n < 255) {
      break;
    }
  }

  while ((pos = headers_data.find(delimiter)) != std::string::npos) {
    std::string line = headers_data.substr(0, pos);

    if (i == 0) {
      request = line;
      i++;
    }

    headers_data.erase(0, pos + delimiter_len);

    size_t colon_pos = line.find(":");
    if (colon_pos != std::string::npos) {
      std::string key = line.substr(0, colon_pos);
      std::string value = line.substr(colon_pos + 2);
      headers[key] = value;
    }
  }

  return request;
}

bool s_socket::submit(int client_socket, const std::string &data) {
  std::string response =
      std::format("HTTP/1.1 200 OK\r\nContent-Length: {}\r\n\r\n {}",
                  data.length(), data.c_str());

  return send(client_socket, response.c_str(), response.length(), 0) > 0;
}

bool s_socket::send_html(int client_socket, const std::string &path) {
  std::string response = "";
  std::ifstream file(path);

  if (file.is_open()) {
    std::string buff;

    while (!file.eof()) {
      std::getline(file, buff);
      response.append(buff);
    }
  }
  return this->submit(client_socket, response);
}

bool s_socket::halt() {
  // Close the connections
  shutdown(server, SHUT_WR);

  return close(server) == 0;
}

bool s_socket::is_active() { return alive; }

void s_socket::handle_connection(int client_socket) {
  wait(client_socket);
  send_html(client_socket, "index.html");

  shutdown(client_socket, SHUT_WR);
  close(client_socket);
}
