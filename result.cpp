#include "result.h"

std::string result::get_result(sqlite3_stmt *stmt, int index)
{
    std::string str;

    int columnType = sqlite3_column_type(stmt, index);

    switch (columnType)
    {
        case SQLITE_TEXT :
            returnText(str, stmt, index);
        break;

        case SQLITE_INTEGER :
            returnInt(str,stmt,index);
        break;

        case SQLITE_FLOAT :
            returnDouble(str,stmt,index);
        break;

        case SQLITE_BLOB :
            returnInt(str,stmt,index);
        break;

        case SQLITE_NULL :
            returnInt(str,stmt,index);
        break;
    }
    return str;
}
void result::returnText (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = (char*)sqlite3_column_text(stmt,index);
}
void result::returnInt (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = std::to_string(sqlite3_column_int(stmt,index));
}
void result::returnDouble (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = std::to_string(sqlite3_column_double(stmt,index));
}
void result::returnBlob (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = (char*)sqlite3_column_blob(stmt,index);
}
void result::returnNull (std::string &data, sqlite3_stmt *stmt, int index)
{
    data = (char*)sqlite3_column_text(stmt,index);
}
