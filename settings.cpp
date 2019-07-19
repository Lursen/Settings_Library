#include "settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>

Settings::Settings(const std::string &path) : DB (path)
{}

Settings::~Settings()
{
    DB.close_connection();
}

void Settings::upd_value(const std::string &id, const std::string &property, const std::string &column, const std::string &data)
{
    std::stringstream ss;

    ss << "UPDATE WidgetSettings SET "<< column <<" = ? WHERE ID = ? AND Property = ?;";

    std::string sql = ss.str();

    std::cout << sql << std::endl;

    DB.get_statement()->prepare_statement(DB.get_database(), sql);

    DB.get_statement()->bind_text(1, data);
    DB.get_statement()->bind_text(2, id);
    DB.get_statement()->bind_text(3, property);

    int rc = DB.get_statement()->execute_statement()->get_result(DB.get_statement()->get_stmt());
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

    DB.get_statement()->prepare_statement(DB.get_database(), sql);

    DB.get_statement()->bind_text(1, id);
    DB.get_statement()->bind_text(2, property);

    int rc = DB.get_statement()->execute_statement()->get_result(DB.get_statement()->get_stmt());
    if (rc)
    {
        DB.rollback_transaction();
    }
    else
    {
      data = DB.get_statement()->execute_statement()->get_result_data()[0][0];
    }
}
