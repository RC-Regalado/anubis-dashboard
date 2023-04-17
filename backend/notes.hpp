//
// Created by rc-regalado on 31/1/22.
//

#ifndef SYNC_NOTES_HPP
#define SYNC_NOTES_HPP
#include <string>
using namespace std;

class notes {
    string name;

public:
    explicit notes(string name);
    void save(const string& value);
};


#endif //SYNC_NOTES_HPP
