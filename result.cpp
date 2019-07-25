#include "result.h"
#include "statement.h"

Result::Result(const std::shared_ptr<Statement>& st) : _stmt(st){}

bool Result::step()
{
    if (sqlite3_step(_stmt->get_stmt()) == SQLITE_ROW)
    {
        return true;
    }
    return false;
}

std::string Result::get_result(int index)
{
    int columnType = sqlite3_column_type(_stmt->get_stmt(), index);
    switch (columnType)
    {
        case SQLITE_TEXT :
           return get_text(index);
        break;

        case SQLITE_INTEGER :
            return std::to_string(get_int(index));
        break;

        case SQLITE_FLOAT :
            return std::to_string(get_double(index));
        break;

        case SQLITE_BLOB :
            return get_blob(index);
        break;

        case SQLITE_NULL :
            return get_null(index);
        break;
    }
}

int Result::get_max_index()
{
    return sqlite3_column_count(_stmt->get_stmt());
}

std::string Result::get_text (int index)
{
    return (char*)sqlite3_column_text(_stmt->get_stmt(),index);
}

int Result::get_int (int index)
{
    return sqlite3_column_int(_stmt->get_stmt(),index);
}

double Result::get_double (int index)
{
    return sqlite3_column_double(_stmt->get_stmt(),index);
}

std::string Result::get_blob (int index)
{
    return (char*)sqlite3_column_blob(_stmt->get_stmt(),index);
}

std::string Result::get_null (int index)
{
    return (char*)sqlite3_column_text(_stmt->get_stmt(),index);
}

