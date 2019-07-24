#include "result.h"
#include "statement.h"

Result::Result(std::shared_ptr<Statement> st) : _stmt(st){}

std::vector<std::vector<std::string>> Result::get_result()
{
    std::vector<std::vector<std::string>> data;
    bool done = false;
    int i = 0;
    int n = 0;
    while (!done)
    {
        switch (sqlite3_step(_stmt->get_stmt()))
        {
        case (SQLITE_ROW):

            n = get_maxIndex();

            data.resize(i+1, std::vector<std::string> (n, ""));

            for (int j = 0; j < n; j++)
            {
                int columnType = sqlite3_column_type(_stmt->get_stmt(), j);
                switch (columnType)
                {
                    case SQLITE_TEXT :
                        data[i][j] = get_text(j);
                    break;

                    case SQLITE_INTEGER :
                        data[i][j] = std::to_string(get_int(j));
                    break;

                    case SQLITE_FLOAT :
                        data[i][j] = std::to_string(get_double(j));
                    break;

                    case SQLITE_BLOB :
                        data[i][j] = get_blob(j);
                    break;

                    case SQLITE_NULL :
                        data[i][j] = get_null(j);
                    break;
                }
            }
            i++;
            break;

        case (SQLITE_DONE):
            done = true;
            break;

        default:
            break;
        }
    }

    return data;
}

int Result::get_maxIndex()
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

