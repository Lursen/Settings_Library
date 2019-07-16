#ifndef RESULT_H
#define RESULT_H
#include "string"
#include "sqlite3.h"


class result
{

public:

    std::string get_result( sqlite3_stmt *stmt, int index);

    void get_Text (std::string &data, sqlite3_stmt *stmt, int index);

    void get_Int (std::string &data, sqlite3_stmt *stmt, int index);

    void get_Double (std::string &data, sqlite3_stmt *stmt, int index);

    void get_Blob (std::string &data, sqlite3_stmt *stmt, int index);

    void get_Null (std::string &data, sqlite3_stmt *stmt, int index);
};

#endif // RESULT_H
