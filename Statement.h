#ifndef STATEMENT_H
#define STATEMENT_H
#include "string"
#include "sqlite3.h"
#include "vector"
#include "result.h"

class Statement
{
    sqlite3_stmt *stmt;

    Statement(const Statement &stmt) = delete;

    Statement& operator=(const Statement &stmt) = delete;

public:
    Statement(sqlite3 *db, const std::string &command);

    ~Statement();

    void bindText(int index, const std::string &parameter);

    void bindInt(int index, int parameter);

    void bindDouble(int index, double parameter);

    void bindBLOB(int index, int parameter, const void *blob, int size);

    void bindNULL(int index);

    void executeStatement(std::string &data);

    void executeStatement(std::vector<std::vector<std::string>> &data);

    void executeStatement();
};

#endif // STATEMENT_H
