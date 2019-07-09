#ifndef STATEMENT_H
#define STATEMENT_H
#include "string"
#include "sqlite3.h"

class Statement
{
public:
    std::string executeStatement(sqlite3 *db, const char *command, std::string *parameters);
};

#endif // STATEMENT_H
