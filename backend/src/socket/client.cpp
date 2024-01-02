#include "client.hpp"
#include "exceptions.hpp"
#include "utils.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <format>
#include <fstream>
#include <iterator>
#include <netinet/in.h> // For sockaddr_in
#include <ostream>
#include <sys/socket.h> // For socket functions
#include <sys/types.h>
#include <thread>
#include <unistd.h> // For read
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

client::client(int socketfd): socketfd(socketfd){

}

void client::handle_connection() {
  receive();
  send_html("index.html");

  shutdown(socketfd, SHUT_WR);
  close(socketfd);
}

std::string client::receive() {
  char buffer[256];
  int n = 1;
  char *end = nullptr;
  std::string headers_data, request;

  unsigned short int i = 0;

  size_t pos = 0;
  const char *delimiter = "\r\n";
  int delimiter_len = strlen(delimiter);

  while (n > 0) {
    n = read(socketfd, buffer, 255);

    if (n < 0)
      throw socket_exception("Failed reading from socket.");
    if (n == 0)
      throw socket_exception("peer shutted down");

    headers_data += std::string(buffer, n);
    if (strcontains(headers_data, "\r\n\r\n") || n < 255) {
      break;
    }
  }

    std::istringstream ss(headers_data);
    std::string line;
    std::string smethod, path, httpVersion;

    ss >> method >> path >> httpVersion;

    this->method = smethod;
    this->uri = path;

    // Almacenar cada línea en un vector
    std::vector<std::string> lines;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    lines

    // Buscar la línea con el método y la ruta
    for (const std::string& line : lines) {
        std::istringstream lineStream(line);
        lineStream >> method >> path;
        // if (!method.empty() && !path.empty()) {
        //     // Se encontró la línea con el método y la ruta
        //     return std::make_pair(method, path);
        // }
    }

 
  std::cout << "End Request" << std::endl;
  return request;
}

bool client::submit(const std::string &data) {
  std::string response =
      std::format("HTTP/1.1 200 OK\r\nContent-Length: {}\r\n\r\n {}",
                  data.length(), data.c_str());

  return send(socketfd, response.c_str(), response.length(), 0) > 0;
}

bool client::send_html(const std::string &path) {
  std::string response = "";
  std::ifstream file(path);

  if (file.is_open()) {
    std::string buff;

    while (!file.eof()) {
      std::getline(file, buff);
      response.append(buff);
    }
  }
  return this->submit(response);
}


