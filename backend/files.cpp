//
// Created by rc-regalado on 29/9/21.
//

#include "files.hpp"
#include "database.hpp"
#include "md5.hpp"

#include <dirent.h>
#include <fstream>
#include <utility>


extern string sync_path;


file::file(const string &id, const string &name, const string &hash) {
    this->properties["id"] = id;
    this->properties["name"] = name;
    this->properties["hash"] = hash;
}

file::file() = default;

string file::to_json() {
    ostringstream os;

    int i = 1;

    for (const auto &pair: properties) {
        os << '"' << pair.first << "\":\"" << pair.second << '"';
        auto end = properties.end();
        if (properties.size() != i++)
            os << ',';
    }

    return '{' + os.str() + '}';
}

vector<string> file::list_directory(const string &_dir) {

    vector<string> files;

    string path = sync_path + "/sources/media/" + _dir;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            string name = ent->d_name;

            if (name == "." || name == "..") continue;

            files.push_back(name);
        }
        closedir(dir);
    }

    return files;

}


media::media(const string &workdir) {

    auto callback = [](void *data, int argc, char **argv, char **colName) {

        auto f = file(argv[0], argv[1], argv[2]);

        ((vector<file> *) data)->push_back(f);
        return 0;
    };

    auto db = database("select id, name, hash from files order by name", workdir + "/sync.db", callback);

    db.read(&_data);
}

media::media(string workdir, string name) : workdir(std::move(workdir)), name(std::move(name)) {}


void media::save(const string &data) {
    auto callback = [](void *data, int argc, char **argv, char **colName) {
        printf("%s", argv[0]);

        return 0;
    };

    string hash = md5(name);

    //language=sqlite
    string query = "insert into files (name, hash, date) values (?, ?, ?)";

    auto db = database(query, workdir + "/sync.db", callback);

    if (!db.create(name, hash))
        return;

    ofstream writer = ofstream (workdir + "/sources/uploads/" + hash);

    writer.write(data.c_str(), data.length());

    writer.close();
}

string media::to_json() {
    ostringstream os;

    int i = 1;
    for (auto item: _data) {
        os << item.to_json();
        if (_data.size() != i++)
            os << ',';
    }

    return '[' + os.str() + ']';
}


string media::download(const string &workdir, const string &hash) {
    stringstream handler;
    handler << ifstream(workdir + "/sources/uploads/" + hash, ios_base::binary).rdbuf();

    return handler.str();
}


