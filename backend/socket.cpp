#include <cstddef>
#include <cstdlib> 
#include <cstring>
#include <iostream>
#include <netinet/in.h> // For sockaddr_in
#include <ostream>
#include <string>
#include <sys/socket.h> // For socket functions
#include <sys/types.h>
#include <unistd.h> // For read
#include <sstream>

int main() {
  // Create a socket (IPv4, TCP)
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Listen to port 9999 on any address
  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(9999); // htons is necessary to convert a number to
                                   // network byte order
  if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 10) < 0) {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Listening -- " << std::endl;
  // Grab a connection from the queue
  auto addrlen = sizeof(sockaddr);
  int connection =
      accept(sockfd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);
  if (connection < 0) {
    std::cout << "Failed to grab connection. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Read from the connection
  char buffer[256];
  int bytesLeft = sizeof(buffer) - sizeof(char);

  int n = 1;

  char* end = nullptr;

  std::stringstream stream;

  while (n > 0) {
    n = read(connection, buffer, 255);

    if (n < 0) {
      std::cerr << "ERROR reading from socket\n";
      break;
    }

    if (n == 0) {
      std::cout << "peer shutted down" << std::endl;
      break;
    }

    stream << buffer;

    end = strstr(buffer, "\r\n\r\n");

    if (end != nullptr || n < 255) {
      break;
    }
  }

  std::string line;

  while(std::getline(stream, line)){
    if (line.compare("\r") == 0) break;

    std::cout << "-- " << line << std::endl;
  }

  // Send a message to the connection
  const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
  send(connection, response, strlen(response), 0);

  // Close the connections
  close(connection);
  close(sockfd);
}
