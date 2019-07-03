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
	void upd_value(int id, int ue_id, string column, string value);

	// Method for loading value from database
	void load_value(int id, int ue_id, string column, string& value, int numeric);
};

#endif // !SETTINGS
