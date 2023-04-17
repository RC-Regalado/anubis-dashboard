//
// Created by rc-regalado on 30/1/22.
//

#ifndef SYNC_DOWNLOAD_HPP
#define SYNC_DOWNLOAD_HPP
#include "files.hpp"

class download : public object {
    bool hide;
    string url;
    string name;

    bool running;

public:
    explicit download(string  url);
    download(string name, string url, bool hide);
    int run();

    void exec();

    string to_json() override;
};

#endif //SYNC_DOWNLOAD_HPP
