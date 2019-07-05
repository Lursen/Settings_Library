#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>
#include "sqlite3.h"

class Settings
{
	sqlite3* db;

public:

	Settings();

	~Settings();

	// Method for updating value in database
	void upd_value(int id, std::string widgetElement, std::string column, std::string value);

	// Method for loading value from database
	void load_value(int id, std::string widgetElement, std::string column, std::string& value, int numeric);

	// Method for loading size of widget/user element
	void load_size(int id, std::string widgetElement, int& x, int& y, int& width, int& lenght);

	// Method for updating size of widget/user element
	void upd_size(int id, std::string widgetElement, int x, int y, int width, int lenght);
};

#endif // !SETTINGS
