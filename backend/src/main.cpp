#include "socket/exceptions.hpp"
#include "socket/socket.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
  try {
    s_socket server;
    if (!server.is_active())
      return EXIT_FAILURE;

    cout << "Listening ---" << endl;
    server.serve();

    if (server.halt()) {
      cout << "Server stop gracefully." << endl;
    } else {
      cerr << "Unexpected error.\n";
    }
  } catch (socket_exception se) {
    cerr << se.what() << '\n';
    return EXIT_FAILURE;
  }

  return 0;
}
