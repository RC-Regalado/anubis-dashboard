#include <iostream>
#include <fstream>
#include "notes.hpp"

#include "files.hpp"
#include "database.hpp"
#include "md5.hpp"
using namespace std;

notes::notes(const string& workdir) {
    auto callback = [](void *data, int argc, char **argv, char **colName) {
        auto f = file(argv[0], argv[1], argv[2]);

        ((vector<file> *) data)->push_back(f);
        return 0;
    };

    auto db = database("select id, name, hash from notes order by name", workdir + "/sync.db", callback);
    db.read(&_data);
}

notes::notes(string workdir, string name) : media(workdir,name)  {}


void notes::save(const string &data) {
    auto callback = [](void *data, int argc, char **argv, char **colName) {
        printf("%s", argv[0]);
        return 0;
    };

    string hash = md5(name);

    //language=sqlite
    string query = "insert into notes (name, hash, date) values (?, ?, ?)";

    auto db = database(query, workdir + "/sync.db", callback);

    if (!db.create(name, hash))
        return;

    ofstream writer = ofstream (workdir + "/sources/notes/" + hash);
    writer.write(data.c_str(), data.length());
    writer.close();
}

string notes::download(const string &workdir, const string &hash){
    stringstream handler;
    handler << ifstream(workdir + "/sources/notes/" + hash, ios_base::binary).rdbuf();

    return handler.str();   
}
