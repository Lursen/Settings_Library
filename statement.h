#ifndef STATEMENT_H
#define STATEMENT_H
#include "string"
#include "sqlite3.h"
#include "vector"
#include "result.h"
#include <memory>

class Statement: public std::enable_shared_from_this<Statement>
{
    sqlite3_stmt *stmt;

    Statement(const Statement &stmt) = delete;

    Statement& operator=(const Statement &stmt) = delete;

public:

    Statement();

    ~Statement();

    void prepare_statement(sqlite3 *db, const std::string &command);

    void finalize_statement();

    void bind_text(int index, const std::string &parameter);

    void bind_int(int index, int parameter);

    void bind_double(int index, double parameter);

    void bind_blob(int index, int parameter, const void *blob, int size);

    void bind_null(int index);

    std::shared_ptr<Result> execute_statement();

    sqlite3_stmt* get_stmt();
};

#endif // STATEMENT_H
