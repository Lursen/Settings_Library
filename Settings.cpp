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
    std::stringstream ss;

    ss << "UPDATE WidgetSettings SET "<< column <<" = ? WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    std::cout << sql << std::endl;

    Statement st(db, sql);

    st.bindText(data, 1);
    st.bindText(id, 2);
    st.bindText(property, 3);

    st.executeStatement();
}

void Settings::load_value(const std::string &id, const std::string &property, const std::string &column, std::vector<std::vector<std::string>> &data)
{
    std::stringstream ss;

    ss << "SELECT " << column << " FROM WidgetSettings WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    Statement st(db, sql);

    st.bindText(id, 1);
    st.bindText(property, 2);

    st.executeStatement(data);
}

