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

Statement* Database::get_statement()
{
    return &st;
}

sqlite3* Database::get_database()
{
    return db;
}

void Database::close_connection()
{
    std::cout << "Database closed" << std::endl ;
    sqlite3_close(db);
}

// New methods

void Database::begin_transaction()
{
    std::string sql = "BEGIN TRANSACTION;";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}

void Database::commit_transaction()
{
    std::string sql = "COMMIT;";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}

void Database::rollback_transaction()
{
    std::string sql = "ROLLBACK;";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}

void Database::journal_delete()
{
    std::string sql = "PRAGMA journal_mode = DELETE";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}

void Database::journal_truncate()
{
    std::string sql = "PRAGMA journal_mode = TRUNCATE";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}

void Database::journal_persist()
{
    std::string sql = "PRAGMA journal_mode = PERSIST";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}

void Database::journal_memory()
{
    std::string sql = "PRAGMA journal_mode = MEMORY";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}

void Database::journal_wal()
{
    std::string sql = "PRAGMA journal_mode = WAL";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}

void Database::journal_off()
{
    std::string sql = "PRAGMA journal_mode = OFF";
    st.prepare_statement(db, sql);
    st.execute_statement()->get_result(st.get_stmt());
}
