#include "database.h"
#include "vector"
#include <iostream>
#include <stdio.h>

Database::Database(const std::string &path)
{
    int rc = sqlite3_open(path.c_str(), &db);
    if (rc)
    {
        // In case of error
        std::cout << "Error while opening database: " << sqlite3_errmsg(db) << std::endl ;
    }
    else
    {
        // Successful opening
        std::cout << "Database opened" << std::endl ;
    }
}

Database::~Database()
{
    std::cout << "Database closed" << std::endl ;
    sqlite3_close(db);
}

std::shared_ptr<Statement> Database::get_statement()
{
    return std::make_shared<Statement>();
}

sqlite3* Database::get_database()
{
    return db;
}

void Database::open_connection(const std::string &path)
{
    int rc = sqlite3_open(path.c_str(), &db);
    if (rc)
    {
        // In case of error
        std::cout << "Error while opening database: " << sqlite3_errmsg(db) << std::endl ;
    }
    else
    {
        // Successful opening
        std::cout << "Database opened" << std::endl ;
    }
}

void Database::close_connection()
{
    std::cout << "Database closed" << std::endl ;
    sqlite3_close(db);
}

void Database::begin_transaction()
{
    std::string sql = "BEGIN TRANSACTION;";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}

void Database::commit_transaction()
{
    std::string sql = "COMMIT;";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}

void Database::rollback_transaction()
{
    std::string sql = "ROLLBACK;";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}

void Database::journal_delete()
{
    std::string sql = "PRAGMA journal_mode = DELETE";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}

void Database::journal_truncate()
{
    std::string sql = "PRAGMA journal_mode = TRUNCATE";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}

void Database::journal_persist()
{
    std::string sql = "PRAGMA journal_mode = PERSIST";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}

void Database::journal_memory()
{
    std::string sql = "PRAGMA journal_mode = MEMORY";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}

void Database::journal_wal()
{
    std::string sql = "PRAGMA journal_mode = WAL";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}

void Database::journal_off()
{
    std::string sql = "PRAGMA journal_mode = OFF";
    get_statement()->prepare_statement(db, sql);
    get_statement()->execute_statement()->get_result();
}
