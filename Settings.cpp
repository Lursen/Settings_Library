#include "Settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cstring>
Settings::Settings()
{
	// Opening database connection
    int rc = sqlite3_open("Settings.db", &db);
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
	// Closing database connection
    std::cout << "Database closed" << std::endl ;
	sqlite3_close(db);
}

void Settings::upd_value(const std::string &id, const std::string &userElement, const std::string &column, const std::string &value)
{
    std::stringstream ss;
    const char * sql;

    std::string parameters [4];
    parameters[1] = value;
    parameters[2] = id;
    parameters[3] = userElement;

    // Updating User Element
    if(userElement.empty() == false)
    {
        ss << "UPDATE USER_ELEMENT SET " << column <<" = ? WHERE WidgetID = ?, UserElementName = ?;";
    }
    else
    {
        ss << "UPDATE WIDGET SET " << column << " = ? WHERE ID = ?;";
    }

    sql = ss.str().c_str();

    st.executeStatement(db, sql, parameters);

    std::cout <<"Database was updated\n";
}

void Settings::load_value(const std::string &id, const std::string &userElement, const std::string &column, std::string& value)
{
    std::stringstream ss;
    const char * sql;

    std::string parameters [3];
    parameters[1] = id;
    parameters[2] = userElement;

    if(userElement.empty() == false)
    {
        ss << "SELECT " << column << " FROM USER_ELEMENT WHERE WidgetID = ?, UserElementName = ?;";
    }
    else
    {
        ss << "SELECT " << column << " FROM WIDGET WHERE ID = ?;";
    }

    sql = ss.str().c_str();

    value = st.executeStatement(db, sql, parameters);

    std::cout << "Data from database was loaded\n";
}

void Settings::load_size(const std::string &id, const std::string &userElement, int &x, int &y, int &width, int &lenght)
{
    std::string value;

    load_value(id, userElement, "CoordinateX",  value);
    x = stoi(value);

    load_value(id, userElement, "CoordinateY",  value);
    y = stoi(value);

    load_value(id, userElement, "Width",  value);
    width = stoi(value);

    load_value(id, userElement, "Lenght",  value);
    lenght = stoi(value);
}

void Settings::upd_size(const std::string &id, const std::string &userElement, int x, int y, int width, int lenght)
{
    std::string value;

    value = std::to_string(x);
    upd_value(id, userElement, "CoordinateX", value);

    value = std::to_string(y);
    upd_value(id, userElement, "CoordinateY",  value);

    value = std::to_string(width);
    upd_value(id, userElement, "Width",  value);

    value = std::to_string(lenght);
    upd_value(id, userElement, "Lenght",  value);
}
