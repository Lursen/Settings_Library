#ifndef DATABASE_H
#define DATABASE_H
#include "string"
#include "sqlite3.h"

class Database
{    
    Database(const Database &db) = delete;

    Database& operator=(const Database &db) = delete;

public:

    sqlite3* db;

    Database(const std::string &path);

    Database();

    ~Database();
};

#endif // DATABASE_H
