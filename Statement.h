#ifndef STATEMENT_H
#define STATEMENT_H
#include "string"
#include "sqlite3.h"
#include "vector"

class Statement
{
    sqlite3_stmt *stmt;

public:
    Statement(sqlite3 *db, const std::string &command);

    ~Statement();

    void bindText(const std::string &parameter, int index);

    void bindInt(int parameter, int index);

    void executeStatement(std::vector<std::vector<std::string>> &data);

    void executeStatement();
};

#endif // STATEMENT_H
