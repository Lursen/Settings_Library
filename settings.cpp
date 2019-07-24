#include "settings.h"
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

    auto st = DB.get_statement();

    st->prepare_statement(DB.get_database(), sql);

    st->bind_text(1, data);
    st->bind_text(2, id);
    st->bind_text(3, property);

    auto rs = st->execute_statement();

    int rc = rs->get_result();
    if (rc)
   {
        DB.rollback_transaction();
   }
}

void Settings::load_value(const std::string &id, const std::string &property, const std::string &column, std::string &data)
{
    std::stringstream ss;

    ss << "SELECT " << column << " FROM WidgetSettings WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    std::shared_ptr<Statement> st = DB.get_statement();

    st->prepare_statement(DB.get_database(), sql);

    st->bind_text(1, id);
    st->bind_text(2, property);

    auto rs = st->execute_statement();

    int rc = st->execute_statement()->get_result();
    if (rc)
    {
        DB.rollback_transaction();
    }
    else
    {
      data = rs->get_result_data()[0][0];
    }
}
