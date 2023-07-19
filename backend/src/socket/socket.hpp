#ifndef __SSOCKET_HPP_
#define __SSOCKET_HPP_
#include <map>
#include <netinet/in.h>
#include <string>

class s_socket {
  bool alive;
  int server;

  std::string method;
  std::string uri;

  std::map<std::string, std::string> headers;
  sockaddr_in sockaddr;

public:
  s_socket();

  void start();
  void wait(int client_socket);
  int accept_connection();
  int serve();

  bool is_active();
  bool submit(int client_socket, const std::string &data);
  bool send_html(int client_socket, const std::string &path);
  std::string receive(int client_socket);

  bool halt();

private:
  void handle_connection(int client_socket);
};

#endif
