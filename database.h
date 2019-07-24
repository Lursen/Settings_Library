#ifndef DATABASE_H
#define DATABASE_H
#include "string"
#include <memory>
#include "sqlite3.h"
#include "statement.h"

class Database
{    
    sqlite3* _db;

    Database(const Database &db) = delete;

    Database& operator=(const Database &db) = delete;

public:

    Database(const std::string &path);

    ~Database();

    std::shared_ptr<Statement> get_statement(std::string);

    sqlite3 *get_database();

    void open_connection(const std::string &path);

    void close_connection();

  // Methods for executing transaction

    void begin_transaction();

    void commit_transaction();

    void rollback_transaction();

  // Methods for changing the journal mode

    void journal_delete();

    void journal_truncate();

    void journal_persist();

    void journal_memory();

    void journal_wal();

    void journal_off();

};

#endif // DATABASE_H
