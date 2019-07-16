#include "database.h"
#include "vector"
#include <iostream>
#include <stdio.h>

Database::Database(const std::string &path)
{
    // Open database connection
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

sqlite3* Database::get_database()
{
    return db;
}

void Database::close_connection()
{
    // Close database connection
    std::cout << "Database closed" << std::endl ;
    sqlite3_close(db);
}

