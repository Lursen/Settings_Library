#ifndef SETTINGS_H
#define SETTINGS_H
#include "database.h"

class Settings
{
    Database _database;

    Settings(const Settings &st) = delete;

    Settings& operator=(const Settings &st) = delete;

public:

    Settings(const std::string &path);

	~Settings();

	// Method for updating value in database
    void upd_value(const std::string &id, const std::string &property, const std::string &column, const std::string &data);

	// Method for loading value from database
    void load_value(const std::string &id, const std::string &property, const std::string &column, std::string &data);

    // Method for creating database with definite structure
    void create_database();
};

#endif // !SETTINGS
