#ifndef SETTINGS_H
#define SETTINGS_H
#include "statement.h"
#include "database.h"

class Settings
{
    Database DB;

    Settings(const Settings &st) = delete;

    Settings& operator=(const Settings &st) = delete;

public:

    Settings(const std::string &path);

	~Settings();

	// Method for updating value in database
    void upd_value(const std::string &id, const std::string &property, const std::string &column, const std::string &data);

	// Method for loading value from database
    void load_value(const std::string &id, const std::string &property, const std::string &column, std::string &data);

    // Methods for executing transaction

    void begin_transaction();

    void commit_transaction();

    void rollback_transaction();

    // Method for creating database with a certain structure
    void create_table();

    // Methods for changing the journal mode

    void journal_delete();

    void journal_truncate();

    void journal_persist();

    void journal_memory();

    void journal_wal();

    void journal_off();
};

#endif // !SETTINGS
