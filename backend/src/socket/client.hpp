#ifndef __CLIENT_HPP_
#define __CLIENT_HPP_

class client {
  int socketfd;

public:
  client(int socketfd);

  void handle_connection();
};

#endif
