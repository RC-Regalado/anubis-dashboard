#ifndef __CLIENT_HPP_
#define __CLIENT_HPP_
#include <netinet/in.h>
#include <string>
#include <map>

class client {
  int socketfd;
  std::string method;
  std::string uri;

  std::map<std::string, std::string> headers;
  sockaddr_in sockaddr;

public:
  client(int socketfd);

  void handle_connection();
  bool submit(const std::string &data);
  bool send_html(const std::string &path);
  std::string receive();
};

#endif
