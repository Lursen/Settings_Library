#ifndef SETTINGS_H
#define SETTINGS_H
#include "Statement.h"

class Settings
{
	sqlite3* db;

public:

    Settings(const std::string &path);

	~Settings();

	// Method for updating value in database
    void upd_value(const std::string &id, const std::string &property, const std::string &column, const std::string &data);

	// Method for loading value from database
    void load_value(const std::string &id, const std::string &property, const std::string &column, std::vector<std::vector<std::string>> &data);
};

#endif // !SETTINGS
