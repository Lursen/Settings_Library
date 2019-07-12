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

void Statement::bindText(int index, const std::string &parameter)
{
    sqlite3_bind_text(stmt, index, parameter.c_str(), std::strlen(parameter.c_str()),0);
}

void Statement::bindInt(int index, int parameter)
{
    sqlite3_bind_int(stmt, index, parameter);
}

void Statement::bindDouble(int index, double parameter)
{
    sqlite3_bind_double(stmt, index, parameter);
}

void Statement::bindBLOB(int index, int parameter, const void *blob, int size)
{
    sqlite3_bind_blob(stmt, index, blob, size, SQLITE_TRANSIENT);
}

void Statement::bindNULL(int index)
{
    sqlite3_bind_null(stmt, index);
}

void Statement::executeStatement()
{
    sqlite3_step(stmt);
}

void Statement::executeStatement(std::string &data)
{
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        data = (char*)sqlite3_column_text(stmt, 0);
    }
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
                int columnType = sqlite3_column_type(stmt, j);

                if (columnType == SQLITE_INTEGER)
                {
                    data[i][j] = std::to_string(sqlite3_column_int(stmt,j));
                }

                if (columnType == SQLITE_FLOAT)
                {
                    data[i][j] = std::to_string(sqlite3_column_double(stmt,j));
                }

                if (columnType == SQLITE_TEXT)
                {
                    data[i][j] =  (char*)sqlite3_column_text(stmt,j);
                }

                if (columnType == SQLITE_BLOB)
                {
                    data[i][j] = (char*)sqlite3_column_blob(stmt,j);
                }

                if (columnType == SQLITE_NULL)
                {
                    data[i][j] = (char*)sqlite3_column_text(stmt,j);
                }
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
