//
// Created by rc-regalado on 25/9/21.
//

#ifndef SYNC_DATABASE_HPP
#define SYNC_DATABASE_HPP

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

#include <sqlite3.h>
#include "files.hpp"

typedef int (*t_callback)(void *data, int argc, char **argv, char **colName);

class database {
    char *error_message;
    int rc;
    string query;
    string path;
    t_callback callback_ptr;

public:
    database(string query, string path, t_callback ptr);

    bool read(vector<file>* f);

    bool create(const string &_name, const string &hash);

    static void error(const string &err, const string &msg = "");

    static void log(const string &msg);
};


#endif //SYNC_DATABASE_HPP
