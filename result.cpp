#include "result.h"
#include "statement.h"

Result::Result(std::shared_ptr<Statement> st) : stmt(st){}

std::vector<std::vector<std::string>> Result::get_result_data()
{
    return data;
}

int Result::get_result()
{
    data.clear();
    bool done = false;
    int i = 0;
    int n = 0;
    while (!done)
    {
        switch (sqlite3_step(stmt->get_stmt()))
        {
        case (SQLITE_ROW):

            n = get_maxIndex();

            data.resize(i+1, std::vector<std::string> (n, ""));

            for (int j = 0; j < n; j++)
            {
              data[i][j] = check_result(j);
            }
            i++;
            break;

        case (SQLITE_DONE):
            done = true;
            return 0;

        default:
            return 1;
        }
    }
}

std::string Result::check_result(int index)
{
    std::string str;

    int columnType = sqlite3_column_type(stmt->get_stmt(), index);

    switch (columnType)
    {
        case SQLITE_TEXT :
            get_text(str, index);
        break;

        case SQLITE_INTEGER :
            get_int(str,index);
        break;

        case SQLITE_FLOAT :
            get_double(str,index);
        break;

        case SQLITE_BLOB :
            get_blob(str,index);
        break;

        case SQLITE_NULL :
            get_null(str,index);
        break;
    }
    return str;
}

int Result::get_maxIndex()
{
    return sqlite3_column_count(stmt->get_stmt());
}


void Result::get_text (std::string &data, int index)
{
    data = (char*)sqlite3_column_text(stmt->get_stmt(),index);
}
void Result::get_int (std::string &data, int index)
{
    data = std::to_string(sqlite3_column_int(stmt->get_stmt(),index));
}
void Result::get_double (std::string &data, int index)
{
    data = std::to_string(sqlite3_column_double(stmt->get_stmt(),index));
}
void Result::get_blob (std::string &data, int index)
{
    data = (char*)sqlite3_column_blob(stmt->get_stmt(),index);
}
void Result::get_null (std::string &data, int index)
{
    data = (char*)sqlite3_column_text(stmt->get_stmt(),index);
}

