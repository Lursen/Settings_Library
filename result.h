#ifndef RESULT_H
#define RESULT_H
#include "string"
#include "sqlite3.h"
#include "vector"
#include <memory>

class Statement;
class Result
{
    std::vector<std::vector<std::string>> data;

    std::shared_ptr<Statement> stmt;

public:

    Result(std::shared_ptr<Statement>);

    std::vector<std::vector<std::string>> get_result_data();

    std::string check_result(int index);

    int get_result();

    int get_maxIndex();

    void get_text (std::string &data, int index);

    void get_int (std::string &data, int index);

    void get_double (std::string &data, int index);

    void get_blob (std::string &data, int index);

    void get_null (std::string &data, int index);
};

#endif // RESULT_H
