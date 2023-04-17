#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <regex>
using namespace std;

#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>

using namespace cgicc;


#include "files.hpp"
#include "download.hpp"
#include "md5.hpp"
#include "notes.hpp"

string sync_path;

void music() {
    string buffer = "[";

    for (auto &file: file::list_directory("video")) {
        buffer += R"({"path":)";
        buffer += "\"/sources/media/video/\",";
        buffer += R"("name":)";
        buffer += '"' + file + '"';
        buffer += R"(, "mime":"video/mp4"},)";
    }
    //buffer.pop_back();

    for (auto &file: file::list_directory()) {
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

void curses() {
    char *ss = getenv("POST");
    cout << (ss == nullptr ? R"({"name": "Hello"})" : ss);
}

enum class headers {
    JSON,
    HTML,
    BLOB
};

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


int main() {
    char *root = getenv("DOCUMENT_ROOT");
    sync_path = root == nullptr ? "/home/rc-regalado/git/Sync" : root;


    char *c_uri = getenv("REQUEST_URI");
    string uri = c_uri == nullptr ? "test" : c_uri;

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
        Cgicc cgi;
        auto fi = cgi.getElement("name");

        if (fi == cgi.getElements().end()) {
            cout << "{\"result\": \"" << **fi << "\"}";
            return 1;
        }

        notes note(**fi);

        fi = cgi.getElement("value");
        if (fi == cgi.getElements().end()) {
            cout << "{\"result\": \"No se especificó el contenido del archivo.\"}";
            return 1;
        }

        note.save(**fi);

        cout << "{\"result\":\"Archivo guardado.\"}";
    } else {
        cout << response(headers::HTML);

        unique_ptr<ifstream> reader = make_unique<ifstream>(ifstream("lib/index.html"));

        string buffer;
        while (!reader->eof()) {
            getline(*reader, buffer);
            cout << buffer;
        }
    }

    return 0;
}
