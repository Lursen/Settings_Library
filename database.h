#ifndef DATABASE_H
#define DATABASE_H
#include "string"
#include "sqlite3.h"

class Database
{    
    sqlite3* db;

    Database(const Database &db) = delete;

    Database& operator=(const Database &db) = delete;

public:

    Database(const std::string &path);

    sqlite3 *get_database();

    void close_connection();
};

#endif // DATABASE_H
