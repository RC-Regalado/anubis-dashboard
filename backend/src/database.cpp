//
// Created by rc-regalado on 25/9/21.
//

#include "database.hpp"
#include <utility>
#include <chrono>
#include <ctime>

void database::error(const string &err, const string &msg) {
    cerr << err << msg << '\n';
}

void database::log(const string &msg) {
    cout << msg << endl;
}

bool database::read(vector<file>* f) {
    sqlite3 *db;

    /* Open database */
    rc = sqlite3_open(path.c_str(), &db);

    if (rc) {
        error("Can't open database: ", sqlite3_errmsg(db));
        return false;
    }

    /* Execute SQL statement */
    rc = sqlite3_exec(db, query.c_str(), callback_ptr, (void *) f, &error_message);

    if (rc != SQLITE_OK) {
        error("SQL error: ", error_message);
        sqlite3_free(error_message);
        return false;
    }
    sqlite3_close(db);
    return true;
}

database::database(string query, string path, int (*ptr)(void *, int, char **, char **))
        : query(std::move(query)), path(move(path)), rc(0), error_message(nullptr), callback_ptr(ptr) {}

bool database::create(const string &_name, const string &hash) {
    sqlite3 *db;

    /* Open database */
    rc = sqlite3_open(path.c_str(), &db);

    if (rc) {
        error("Can't open database: ", sqlite3_errmsg(db));
        return false;
    } else {
        log("Opened database successfully\n");
    }


    sqlite3_stmt* stmt_insert_ = nullptr;


    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt_insert_, nullptr)) {
        fprintf(stderr, "error: Prepare stmt stmt_insert_ failed, %s\n", sqlite3_errmsg(db));
        return false;
    }

    rc = sqlite3_bind_text(stmt_insert_, 1, _name.c_str(), _name.length(), nullptr);
    if (rc) {
        fprintf(stderr, "error: Bind %s to %d failed, %s\n", _name.c_str(), rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    rc = sqlite3_bind_text(stmt_insert_, 2, hash.c_str(), hash.length(), nullptr);
    if (rc) {
        fprintf(stderr, "error: Bind %s to %d failed, %s\n", hash.c_str(), rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

    auto start = std::chrono::system_clock::now();
    time_t time = start.time_since_epoch().count();
    rc= sqlite3_bind_int64(stmt_insert_, 3, time);
    if (rc) {
        fprintf(stderr, "error: Bind %ld to %d failed, %s\n", time, rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }
    /* Execute SQL statement */
    rc = sqlite3_step(stmt_insert_);

    if(SQLITE_DONE != rc) {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s\n", rc, sqlite3_errmsg(db));
    } else {
        printf("INSERT completed\n\n");
    }
    
    sqlite3_finalize(stmt_insert_);
    sqlite3_close(db);
    return true;

}
