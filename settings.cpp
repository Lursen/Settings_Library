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

    Statement st(DB.get_database(), sql);

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

    Statement st(DB.get_database(), sql);

    st.bindText(1, id);
    st.bindText(2, property);

    st.executeStatement(data);
}

void Settings::begin_transaction()
{
    std::string sql = "BEGIN TRANSACTION;";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}

void Settings::commit_transaction()
{
    std::string sql = "COMMIT;";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}

void Settings::rollback_transaction()
{
    std::string sql = "ROLLBACK;";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}

void Settings::create_table()
{

    std::string sql = "CREATE TABLE WidgetSettings ("     \
                      "ID       TEXT NOT NULL,"           \
                      "Property	TEXT NOT NULL,"           \
                      "Type 	INTEGER,"                 \
                      "Value    TEXT,"                    \
                      "PRIMARY KEY(\"ID\",\"Property\"));";

    Statement st (DB.get_database(), sql);
    st.executeStatement();
}

void Settings::journal_delete()
{
    std::string sql = "PRAGMA journal_mode = DELETE";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}

void Settings::journal_truncate()
{
    std::string sql = "PRAGMA journal_mode = TRUNCATE";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}

void Settings::journal_persist()
{
    std::string sql = "PRAGMA journal_mode = PERSIST";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}

void Settings::journal_memory()
{
    std::string sql = "PRAGMA journal_mode = MEMORY";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}

void Settings::journal_wal()
{
    std::string sql = "PRAGMA journal_mode = WAL";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}

void Settings::journal_off()
{
    std::string sql = "PRAGMA journal_mode = OFF";
    Statement st(DB.get_database(), sql);
    st.executeStatement();
}
