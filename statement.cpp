#include "statement.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

Statement::Statement()
{
    std::cout << "Statement object created\n";
}

Statement::~Statement()
{
    sqlite3_finalize(stmt);
}

sqlite3_stmt* Statement::get_stmt()
{
    return stmt;
}

void Statement::prepare_statement(sqlite3 *db, const std::string &command)
{
    int rc = sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        std::cout << "Statement wasn't prepared\n";
        sqlite3_finalize(stmt);
        return;
    }
    std::cout << "Statement prepared\n";
}

void Statement::bind_text(int index, const std::string &parameter)
{
    std::cout << "Binding statement\n";
    sqlite3_bind_text(stmt, index, parameter.c_str(), std::strlen(parameter.c_str()),0);
}

void Statement::bind_int(int index, int parameter)
{
    sqlite3_bind_int(stmt, index, parameter);
}

void Statement::bind_double(int index, double parameter)
{
    sqlite3_bind_double(stmt, index, parameter);
}

void Statement::bind_blob(int index, int parameter, const void *blob, int size)
{
    sqlite3_bind_blob(stmt, index, blob, size, SQLITE_TRANSIENT);
}

void Statement::bind_null(int index)
{
    sqlite3_bind_null(stmt, index);
}

std::shared_ptr<Result> Statement::execute_statement()
{
    return std::make_shared<Result>(shared_from_this());
}
