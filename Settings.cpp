#include "Settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>

Settings::Settings(const std::string &path)
{
    // Open database connection
    int rc = sqlite3_open(path.c_str(), &db);
	if (rc)
	{
		// In case of error
        std::cout << "Error in opening database: " << sqlite3_errmsg(db) << std::endl ;
	}
	else
	{
		// Successful opening
        std::cout << "Database opened" << std::endl ;
	}
}

Settings::~Settings()
{
    // Close database connection
    std::cout << "Database closed" << std::endl ;
	sqlite3_close(db);
}

void Settings::upd_value(const std::string &id, const std::string &property, const std::string &column, const std::string &data)
{
    const char * sql;
    std::stringstream ss;

    std::string parameters [4];
    parameters[1] = data;
    parameters[2] = id;
    parameters[3] = property;

    ss << "UPDATE WidgetSettings SET "<< column <<" = ? WHERE ID = ? AND Property = ?;";

    sql = ss.str().c_str();

    std::cout << sql << std::endl;

    Statement st(db, sql);
    st.bindParameters(parameters);
    st.executeStatement();
}

void Settings::load_value(const std::string &id, const std::string &property, const std::string &column, std::string &data)
{
    const char * sql;
    std::stringstream ss;

    std::string parameters [3];
    parameters[1] = id;
    parameters[2] = property;

    ss << "SELECT " << column << " FROM WidgetSettings WHERE ID = ? AND Property = ?;";

    sql = ss.str().c_str();

    Statement st(db, sql);
    st.bindParameters(parameters);
    data = st.executeStatement();
}

