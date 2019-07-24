#include "settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>

Settings::Settings(const std::string &path) : _DB (path)
{}

Settings::~Settings()
{}

void Settings::upd_value(const std::string &id, const std::string &property, const std::string &column, const std::string &data)
{
    std::stringstream ss;

    ss << "UPDATE WidgetSettings SET "<< column <<" = ? WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    std::cout << sql << std::endl;

    auto st = _DB.get_statement(sql);

    auto rs = st->execute_statement(_DB.get_database());

    if (rs == NULL)
    {
        _DB.rollback_transaction();
    }

    else
    {
        st->bind_text(1, data);
        st->bind_text(2, id);
        st->bind_text(3, property);

        rs->get_result();
    }
}

void Settings::load_value(const std::string &id, const std::string &property, const std::string &column, std::string &data)
{
    std::stringstream ss;

    ss << "SELECT " << column << " FROM WidgetSettings WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    auto st = _DB.get_statement(sql);

    auto rs = st->execute_statement(_DB.get_database());

    if (rs == NULL)
    {
        _DB.rollback_transaction();
    }

    else
    {
        st->bind_text(1, id);
        st->bind_text(2, property);

        data = rs->get_result()[0][0];
    }
}
