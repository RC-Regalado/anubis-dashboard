#ifndef __CLIENT_HPP_
#define __CLIENT_HPP_
#include <map>
#include <memory>
#include <netinet/in.h>
#include <string>

class client : public std::enable_shared_from_this<client> {
  int socketfd;
  std::string method;
  std::string uri;

  std::map<std::string, std::string> headers;
  sockaddr_in sockaddr;

  std::string boundary;

public:
  client(int socketfd, char *wwwroot);

  void handle_connection();
  bool submit(const std::string &data);
  void parse_headers(std::stringstream &stream);
  bool send_html(const std::string &path);
  std::string receive();
};

#endif
