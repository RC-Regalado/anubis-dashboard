#ifndef __HANDLER_HPP_
#define __HANDLER_HPP_
#include <string>
#include <map>

class handler {
  bool alive;
  int server;
  int client;

  std::string method;
  std::string uri;

  std::map<std::string, std::string> headers;

public:
  handler();

  void start();
  bool is_active();
  bool submit(const std::string& data);
  bool send_html(const std::string& path);
  std::string receive();

  bool halt();
};

#endif
