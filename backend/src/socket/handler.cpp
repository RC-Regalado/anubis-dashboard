#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <format>
#include <fstream>
#include <netinet/in.h> // For sockaddr_in
#include <string>
#include <sys/socket.h> // For socket functions
#include <sys/types.h>
#include <unistd.h> // For read

#include "exceptions.hpp"
#include "handler.hpp"
bool strcontains(const std::string &str, const char *substr) {
  return str.find(substr) != std::string::npos;
}

handler::handler() {
  try {
    start();
    send_html("index.html");
    alive = true;
  } catch (socket_exception se) {
    throw se;
    alive = false;
  }
}

void handler::start() {
  // Create a socket (IPv4, TCP)
  server = socket(AF_INET, SOCK_STREAM, 0);
  if (server == -1)
    throw socket_exception("Failed to create socket.");

  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(9999);

  if (bind(server, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    throw socket_exception("Failed to bind to port 9999.");
  if (listen(server, 10) < 0)
    throw socket_exception("Failed to listen on socket.");

  auto addrlen = sizeof(sockaddr);
  client = accept(server, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

  if (client < 0) {
    throw socket_exception("Failed to grab connection.");
  }
}

std::string handler::receive() {
  char buffer[256];
  int n = 1;
  char *end = nullptr;
  std::string headers_data = "";

  while (n > 0) {
    n = read(client, buffer, 255);

    if (n < 0)
      throw socket_exception("Failed reading from socket.");
    if (n == 0)
      throw socket_exception("peer shutted down");

    headers_data += std::string(buffer, n);

    if (strcontains(headers_data, "\r\n\r\n") || n < 255) {
      break;
    }
  }

  size_t pos = 0;
  const char *delimiter = "\r\n";
  int delimiter_len = strlen(delimiter);

  while ((pos = headers_data.find(delimiter)) != std::string::npos) {
    std::string line = headers_data.substr(0, pos);
    headers_data.erase(0, pos + delimiter_len);

    size_t colon_pos = line.find(":");
    if (colon_pos != std::string::npos) {
      std::string key = line.substr(0, colon_pos);
      std::string value = line.substr(colon_pos + 2);
      headers[key] = value;
    }
  }

  return "";
}

bool handler::submit(const std::string &data) {
  std::string response =
      std::format("HTTP/1.1 200 OK\r\nContent-Length: {}\r\n\r\n {}",
                  data.length(), data.c_str());

  return send(client, response.c_str(), response.length(), 0) > 0;
}

bool handler::send_html(const std::string &path) {
  std::string response = "";
  std::ifstream file(path);

  if (file.is_open()) {
    std::string buff;

    while (!file.eof()) {
      std::getline(file, buff);
      response.append(buff + '\n');
    }
  }
  return this->submit(response);
}

bool handler::halt() {
  // Close the connections
  shutdown(client, SHUT_WR);
  shutdown(server, SHUT_WR);

  int cc = close(client);
  int cs = close(server);

  sleep(2);

  return cc < 0 && cs < 0;
}

bool handler::is_active() {
  return alive;
}
