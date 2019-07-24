#ifndef RESULT_H
#define RESULT_H
#include "string"
#include "sqlite3.h"
#include "vector"
#include <memory>

class Statement;
class Result
{
    std::shared_ptr<Statement> _stmt;

public:

    Result(std::shared_ptr<Statement>);

    std::string get_result(int index);

    bool step();

    int get_max_index();

    std::string get_text (int index);

    int get_int          (int index);

    double get_double    (int index);

    std::string get_blob (int index);

    std::string get_null (int index);
};

#endif // RESULT_H
