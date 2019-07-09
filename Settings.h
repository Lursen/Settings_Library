#ifndef SETTINGS_H
#define SETTINGS_H
#include "Statement.h"

class Settings
{
	sqlite3* db;
    Statement st;

public:

	Settings();

	~Settings();

	// Method for updating value in database
    void upd_value(const std::string &id, const std::string &userElement, const std::string &column, const std::string &value);

	// Method for loading value from database
    void load_value(const std::string &id, const std::string &widgetElement, const std::string &column, std::string& value);

    // Method for loading size of widget/user element from database
    void load_size(const std::string &id, const std::string &widgetElement, int& x, int& y, int& width, int& lenght);

    // Method for updating size of widget/user element in database
    void upd_size(const std::string &id, const std::string &widgetElement, int x, int y, int width, int lenght);
};

#endif // !SETTINGS
