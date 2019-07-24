#include "statement.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

Statement::Statement(std::string command) : _sql(command)
{
    std::cout << "Statement object created\n";
}

Statement::~Statement()
{
    sqlite3_finalize(_stmt);
}

sqlite3_stmt* Statement::get_stmt()
{
    return _stmt;
}

void Statement::finalize_statement()
{
    sqlite3_finalize(_stmt);
}

void Statement::bind_text(int index, const std::string &parameter)
{
    std::cout << "Binding statement\n";
    sqlite3_bind_text(_stmt, index, parameter.c_str(), std::strlen(parameter.c_str()),0);
}

void Statement::bind_int(int index, int parameter)
{
    sqlite3_bind_int(_stmt, index, parameter);
}

void Statement::bind_double(int index, double parameter)
{
    sqlite3_bind_double(_stmt, index, parameter);
}

void Statement::bind_blob(int index, int parameter, const void *blob, int size)
{
    sqlite3_bind_blob(_stmt, index, blob, size, SQLITE_TRANSIENT);
}

void Statement::bind_null(int index)
{
    sqlite3_bind_null(_stmt, index);
}

std::shared_ptr<Result> Statement::execute_statement(sqlite3 *db)
{
    int rc = sqlite3_prepare_v2( db, _sql.c_str(), -1, &_stmt, NULL);

    if (rc != SQLITE_OK)
    {
        std::cout << "Statement wasn't prepared\n";
        sqlite3_finalize(_stmt);
        return NULL;
    }
    std::cout << "Statement prepared\n";
    return std::make_shared<Result>(shared_from_this());
}
