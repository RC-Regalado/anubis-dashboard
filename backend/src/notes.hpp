//
// Created by rc-regalado on 31/1/22.
//

#ifndef SYNC_NOTES_HPP
#define SYNC_NOTES_HPP
#include "files.hpp"
#include <string>
using namespace std;

class notes : public media {
public:
    explicit notes(const string& workdir);
    notes(string workdir, string name);
    void save(const string& value);

    static string download(const string& workdir, const string& hash);
};


#endif //SYNC_NOTES_HPP
