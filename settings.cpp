#include "settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>

Settings::Settings(const std::string &path) : _database (path)
{}

Settings::~Settings()
{}

bool Settings::upd_value(const std::string &id, const std::string &property, const std::string &column, const std::string &data)
{
    std::stringstream ss;

    ss << "UPDATE WidgetSettings SET "<< column <<" = ? WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    std::cout << sql << std::endl;

    auto st = _database.get_statement(sql);

    auto rs = st->execute_statement(_database.get_database());

    if (rs == nullptr)
    {
        _database.rollback_transaction();
        return false;
    }
        st->bind_text(1, data);
        st->bind_text(2, id);
        st->bind_text(3, property);

        rs->step();
        return true;
}

bool Settings::load_value(const std::string &id, const std::string &property, const std::string &column, std::string &data)
{
    std::stringstream ss;

    ss << "SELECT " << column << " FROM WidgetSettings WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    std::cout << sql << std::endl;

    auto st = _database.get_statement(sql);

    auto rs = st->execute_statement(_database.get_database());

    if (rs == nullptr)
    {
        _database.rollback_transaction();
        return false;
    }

        st->bind_text(1, id);
        st->bind_text(2, property);

        rs->step();

        data = rs->get_result(0);
        return true;
}

void Settings::create_database()
{
    std::string sql = "CREATE TABLE IF NOT EXIST WidgetSettings ("    \
                         "ID       TEXT NOT NULL,"       \
                         "Property	TEXT NOT NULL,"      \
                         "Type 	INTEGER,"                \
                         "Value    TEXT,"                \
                         "PRIMARY KEY(\"ID\",\"Property\"));";

    auto st = _database.get_statement(sql);

    auto rs = st->execute_statement(_database.get_database());

    rs->step();
}
