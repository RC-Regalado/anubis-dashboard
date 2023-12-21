#include "client.hpp"
#include "exceptions.hpp"
#include "utils.hpp"

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <format>
#include <fstream>
#include <iterator>
#include <netinet/in.h> // For sockaddr_in
#include <ostream>
#include <string>
#include <sys/socket.h> // For socket functions
#include <sys/types.h>
#include <thread>
#include <unistd.h> // For read

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

  std::cout << headers_data << std::endl;

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

      std::cout << key << " - " << value << std::endl;
    }
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



