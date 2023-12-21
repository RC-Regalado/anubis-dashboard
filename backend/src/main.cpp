#include "socket/client.hpp"
#include "socket/exceptions.hpp"
#include "socket/socket.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
using namespace std;

#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>

using namespace cgicc;

#include "download.hpp"
#include "files.hpp"
#include "notes.hpp"

string sync_path;

// Response headers {{{
enum class headers { JSON, HTML, BLOB };

const char *response(const headers &type) {
  switch (type) {
  case headers::BLOB:
    return "Content-type:application/octet-stream\r\n\r\n";
  case headers::JSON:
    return "Content-type:application/json\r\n\r\n";
  case headers::HTML:
    return "Content-type:text/html\r\n\r\n";
  default:
    return "Content-type:text/plain\r\n\r\n";
  }
}
// }}}

// Music GET {{{
//
void music() {
  string buffer = "[";

  for (auto &file : file::list_directory("video")) {
    buffer += R"({"path":)";
    buffer += "\"/sources/media/video/\",";
    buffer += R"("name":)";
    buffer += '"' + file + '"';
    buffer += R"(, "mime":"video/mp4"},)";
  }
  // buffer.pop_back();

  for (auto &file : file::list_directory()) {
    buffer += R"({"path":)";
    buffer += "\"/sources/media/music/\",";
    buffer += +R"("name":)";
    buffer += '"' + file + '"';
    buffer += R"(, "mime":"video/mp4"},)";
  }

  buffer.pop_back();
  buffer += "]";

  cout << buffer;
}

// }}}

bool read_file(const string &key) {
  Cgicc cgi;
  auto file = cgi.getFile("file");

  string method = getenv("REQUEST_METHOD");

  if (file != cgi.getFiles().end() && method == "POST") {
    cout << HTTPContentHeader(file->getDataType());

    auto handler = media(sync_path, file->getFilename());
    handler.save(file->getData());

    return true;
  }
  return false;
}

void file_handler() {
  Cgicc cgi;
  auto hash = cgi.getElement("hash");
  if (hash != cgi.getElements().end()) {
    cout << media::download(sync_path, hash->getValue());
    return;
  }

  auto file = cgi.getFile("file");

  string method = getenv("REQUEST_METHOD");

  if (file != cgi.getFiles().end() && method == "POST") {
    cout << HTTPContentHeader(file->getDataType());

    auto handler = media(sync_path, file->getFilename());
    handler.save(file->getData());

    return;
  }
  cout << media(sync_path).to_json();
}

void notes_handler() {
  Cgicc cgi;
  auto hash = cgi.getElement("hash");
  if (hash != cgi.getElements().end()) {
    cout << notes::download(sync_path, hash->getValue());
    return;
  }
  auto file = cgi.getElement("name");

  char *tmp = getenv("REQUEST_METHOD");
  string method = tmp == nullptr ? "GET" : tmp;

  if (file != cgi.getElements().end() && method == "POST") {
    cout << response(headers::JSON);

    auto handler = notes(sync_path, file->getValue());
    handler.save(cgi.getElement("value")->getValue());

    return;
  }

  // if (read_file("notes")) return;

  cout << notes(sync_path).to_json();
}

void curses() {
  char *ss = getenv("POST");
  cout << (ss == nullptr ? R"({"name": "Hello"})" : ss);
}

void handle_connection(){

}

// Entry Point {{{
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

int main_bakup() {
  char *root = getenv("DOCUMENT_ROOT");
  sync_path = root == nullptr ? "/home/rc-regalado/git/Sync" : root;

  char *c_uri = getenv("REQUEST_URI");
  string uri = c_uri == nullptr ? "/notes" : c_uri;

  bool hash = regex_match(uri, regex("\\/file(\\?hash=(.)+)?"));

  if (hash && uri != "/file")
    cout << response(headers::BLOB);
  else if (uri != "/")
    cout << response(headers::JSON);

  if (uri == "/screen") {
    system("/home/rc-regalado/.bin/off");
  } else if (uri == "/music") {
    music();
  } else if (hash) {
    file_handler();
  } else if (uri == "/curses") {
    curses();
  } else if (uri == "/download") {
    Cgicc cgi;

    auto url = cgi.getElement("url");
    auto name = cgi.getElement("name");
    auto hide = cgi.queryCheckbox("hide");

    auto *downloader = new download(name->getValue(), url->getValue(), hide);
    downloader->run();
  } else if (uri == "/notes") {
    notes_handler();
  } else {
    cout << response(headers::HTML);

    unique_ptr<ifstream> reader =
        make_unique<ifstream>(ifstream("lib/index.html"));

    string buffer;
    while (!reader->eof()) {
      getline(*reader, buffer);
      cout << buffer;
    }
  }

  return 0;
}
// }}}
