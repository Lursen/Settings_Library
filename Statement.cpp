#include "Statement.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

Statement::Statement(sqlite3 *db, const std::string &command)
{
    int rc = sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, NULL);

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

void Statement::bindText(const std::string &parameter, int index)
{
    sqlite3_bind_text(stmt, index, parameter.c_str(), std::strlen(parameter.c_str()),0);
}

void Statement::bindInt(int parameter, int index)
{
    sqlite3_bind_int(stmt, index, parameter);
}

void Statement::executeStatement()
{
    sqlite3_step(stmt);
}

void Statement::executeStatement(std::vector<std::vector<std::string>> &data)
{
    bool done = false;
    int i = 0;
    int n = 0;
    while (!done)
    {
        switch (sqlite3_step(stmt))
        {
        case (SQLITE_ROW):

            n = sqlite3_column_count(stmt);

            data.resize(i+1, std::vector<std::string> (n, ""));

            for (int j = 0; j < n; j++)
            {
                data[i][j] = (char*)sqlite3_column_text(stmt,j);
            }
            i++;
            break;

        case (SQLITE_DONE):
            done = true;
            break;

        default:
            break;
        }
    }
}
