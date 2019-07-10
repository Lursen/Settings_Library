#ifndef STATEMENT_H
#define STATEMENT_H
#include "string"
#include "sqlite3.h"

class Statement
{
    sqlite3_stmt *stmt;

public:
    Statement(sqlite3 *db, const char *command);
    ~Statement();
    void bindParameters(std::string *parameters);
    std::string executeStatement();
};

#endif // STATEMENT_H
