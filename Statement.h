#ifndef STATEMENT_H
#define STATEMENT_H
#include "string"
#include "sqlite3.h"
#include "vector"
#include "result.h"

class Statement
{
    sqlite3_stmt *stmt;

    Result rs;

    Statement(const Statement &stmt) = delete;

    Statement& operator=(const Statement &stmt) = delete;

public:

    Statement();

    void prepare_statement(sqlite3 *db, const std::string &command);

    void bind_text(int index, const std::string &parameter);

    void bind_int(int index, int parameter);

    void bind_double(int index, double parameter);

    void bind_blob(int index, int parameter, const void *blob, int size);

    void bind_null(int index);

    Result* execute_statement();

    sqlite3_stmt* get_stmt();
};

#endif // STATEMENT_H
