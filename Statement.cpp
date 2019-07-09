#include "Statement.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

std::string Statement::executeStatement(sqlite3 *db, const char *command, std::string *parameters)
{
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, command, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        std::cout << "Error while preparing statement\n";
        sqlite3_finalize(stmt);
        return "Error while preparing statement";
    }

    std::cout <<"Statement successfully prepared\n";
    int n = sqlite3_bind_parameter_count(stmt);

    for (int i = 1; i <= n; i++)
    {
        sqlite3_bind_text(stmt, i, parameters[i].c_str(), std::strlen(parameters[i].c_str()),0);
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::cout <<"Row found\n";
        std::string str(reinterpret_cast<char const*>(sqlite3_column_text(stmt, 0)), 500);
        sqlite3_finalize(stmt);
        return str;
    }
    sqlite3_finalize(stmt);
    std::cout << "Data updated\n";
    return "Statement successfully executed";
}
