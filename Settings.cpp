#include "Settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>

Settings::Settings(const std::string &path) : DB (path)
{}

Settings::~Settings()
{}

void Settings::upd_value(const std::string &id, const std::string &property, const std::string &column, const std::string &data)
{
    std::stringstream ss;

    ss << "UPDATE WidgetSettings SET "<< column <<" = ? WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    std::cout << sql << std::endl;

    Statement st(DB.db, sql);

    st.bindText(1, data);
    st.bindText(2, id);
    st.bindText(3, property);

    st.executeStatement();
}

void Settings::load_value(const std::string &id, const std::string &property, const std::string &column, std::string &data)
{
    std::stringstream ss;

    ss << "SELECT " << column << " FROM WidgetSettings WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    Statement st(DB.db, sql);

    st.bindText(1, id);
    st.bindText(2, property);

    st.executeStatement(data);
}

void Settings::create_table()
{

    std::string sql = "CREATE TABLE WidgetSettings ("     \
                      "ID       TEXT NOT NULL,"           \
                      "Property	TEXT NOT NULL,"           \
                      "Type 	INTEGER,"                 \
                      "Value    TEXT,"                    \
                      "PRIMARY KEY(\"ID\",\"Property\"));";

    Statement st (DB.db, sql);
    st.executeStatement();
}
