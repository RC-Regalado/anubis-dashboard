//
// Created by rc-regalado on 29/9/21.
//

#ifndef SYNC_FILES_HPP
#define SYNC_FILES_HPP
#include <string>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

enum class mime{
    MUSIC,
    IMAGE,
    VIDEO,
    OTHER
};

class object {
public:
    virtual string to_json() = 0;
};

class file : public  object{
protected:
    map<string, string> properties;
    file();
public:
    file(const string& id, const string& name, const string& hash);

    string to_json() override;
    static vector<string> list_directory(const string &_dir = "music");
};

class media : public file {
protected:
    vector<file> _data;

    string workdir;
    string name;

public:
    media();
    explicit media(const string& workdir);
    media(string  workdir, string  name);

    void save(const string& data);
    string to_json() override;

    static string download(const string& workdir, const string& hash);
};

#endif //SYNC_FILES_HPP
