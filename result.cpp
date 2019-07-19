#include "result.h"

std::vector<std::vector<std::string>> Result::get_result_data()
{
    return data;
}

int Result::get_result(sqlite3_stmt *stmt)
{
    data.clear();
    bool done = false;
    int i = 0;
    int n = 0;
    while (!done)
    {
        switch (sqlite3_step(stmt))
        {
        case (SQLITE_ROW):

            n = sqlite3_column_count(stmt);

            data.resize(i+1, std::vector<std::string> (n, ""));

            for (int j = 0; j < n; j++)
            {
              data[i][j] = check_result(stmt, j);
            }

            i++;
            break;

        case (SQLITE_DONE):
            done = true;
            sqlite3_finalize(stmt);
            return 0;

        default:
            sqlite3_finalize(stmt);
            return 1;
        }
    }
}

std::string Result::check_result(sqlite3_stmt *stmt, int index)
{
    std::string str;

    int columnType = sqlite3_column_type(stmt, index);

    switch (columnType)
    {
        case SQLITE_TEXT :
            get_text(str, stmt, index);
        break;

        case SQLITE_INTEGER :
            get_int(str,stmt,index);
        break;

        case SQLITE_FLOAT :
            get_double(str,stmt,index);
        break;

        case SQLITE_BLOB :
            get_blob(str,stmt,index);
        break;

        case SQLITE_NULL :
            get_null(str,stmt,index);
        break;
    }
    return str;
}
void Result::get_text (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = (char*)sqlite3_column_text(stmt,index);
}
void Result::get_int (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = std::to_string(sqlite3_column_int(stmt,index));
}
void Result::get_double (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = std::to_string(sqlite3_column_double(stmt,index));
}
void Result::get_blob (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = (char*)sqlite3_column_blob(stmt,index);
}
void Result::get_null (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = (char*)sqlite3_column_text(stmt,index);
}

