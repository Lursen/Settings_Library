#ifndef RESULT_H
#define RESULT_H
#include "string"
#include "sqlite3.h"
#include "vector"

class Result
{
    std::vector<std::vector<std::string>> data;

public:

    std::vector<std::vector<std::string>> get_result_data();

    std::string check_result( sqlite3_stmt *stmt, int index);

    int get_result(sqlite3_stmt *stmt);

    void get_text (std::string &data, sqlite3_stmt *stmt, int index);

    void get_int (std::string &data, sqlite3_stmt *stmt, int index);

    void get_double (std::string &data, sqlite3_stmt *stmt, int index);

    void get_blob (std::string &data, sqlite3_stmt *stmt, int index);

    void get_null (std::string &data, sqlite3_stmt *stmt, int index);
};

#endif // RESULT_H
