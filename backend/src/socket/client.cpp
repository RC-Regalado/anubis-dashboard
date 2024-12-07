#include "client.hpp"
#include "../tools/utils.hpp"
#include "exceptions.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <netinet/in.h> // For sockaddr_in
#include <ostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/socket.h> // For socket functions
#include <sys/types.h>
#include <unistd.h> // For read

client::client(int socketfd, char *wwwroot) : socketfd(socketfd) {}

void client::handle_connection() {
  receive();

  send_html(uri == "/" ? "/index.html" : uri);

  shutdown(socketfd, SHUT_WR);
  close(socketfd);
}

void client::parse_headers(std::stringstream &sstream) {
  std::string line;
  std::string httpVersion;
  std::string key, value;

  sstream >> method >> uri >> httpVersion;

  headers["version"] = httpVersion;

  while (std::getline(sstream, line)) {
    auto pos = line.find(':');

    if (pos != std::string::npos) {
      key = line.substr(0, pos);
      value = line.substr(pos + 2, line.length() - pos);
    }

    debug(key);
    debug(value);

    headers[key] = value;
  }
}

std::string client::receive() {
  char buffer[256];
  std::string headers_data;
  std::stringstream request;
  size_t flag = 0;
  const char *delimiter = "\r\n";
  FILE *file = fdopen(socketfd, "r+");

  if (file == nullptr) {
    std::cerr << "Error al vincular socket con FILE*" << std::endl;
    close(socketfd);
  }

  while (flag <= 0) {
    if (fgets(buffer, sizeof(buffer), file) == nullptr)
      throw socket_exception("Failed reading from socket.");

    request << buffer;
    flag = strspn(buffer, "\r\n");
  }

  this->parse_headers(request);

  return request.str();
}

bool client::submit(const std::string &data) {
  std::string response =
      std::format("HTTP/1.1 200 OK\r\nContent-Length: {}\r\n\r\n {}",
                  data.length(), data.c_str());

  return send(socketfd, response.c_str(), response.length(), 0) > 0;
}

bool client::send_html(const std::string &path) {
  std::string response = "";
  std::ifstream file(std::filesystem::current_path().string() + path);

  debug(path);

  if (file.is_open()) {
    std::string buff;

    while (!file.eof()) {
      std::getline(file, buff);
      response.append(buff);
    }
  } else {
    debug("non");
  }
  return this->submit(response);
}
