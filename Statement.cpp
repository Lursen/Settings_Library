#include "Statement.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

Statement::Statement(sqlite3 *db,  const char *command)
{
    int rc = sqlite3_prepare_v2(db, command, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        return;
    }
}

Statement::~Statement()
{
    sqlite3_finalize(stmt);
}

void Statement::bindParameters(std::string *parameters)
{
    int n = sqlite3_bind_parameter_count(stmt);
    for (int i = 1; i <= n; i++)
    {
        sqlite3_bind_text(stmt, i, parameters[i].c_str(), std::strlen(parameters[i].c_str()),0);
    }
}

std::string Statement::executeStatement()
{
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
       // std::string str(reinterpret_cast<char const*>(sqlite3_column_text(stmt, 0)), 500);
        std::string str = (char*)sqlite3_column_text(stmt, 0);
        return str;
    }
    if (rc == SQLITE_DONE)
    {
        return "Execution done";
    }
    return "Execution failed";
}

