#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>
#include "sqlite3.h"

class Settings
{
	sqlite3* db;
	int rc;

public:

	// Конструктор

	Settings();

	// Деструктор

	~Settings();

	// Функции для сохранения настроек приложения

	// Функция сохранения численных значений
	void upd_integer(int id, int ue_id, string column, int numeric);

	// Функция сохранения символьных значений
	void upd_char(int id, int ue_id, string column, string value);

	// Функции для загрузки сохранённых настроек приложения

	// Функция загрузки численных значений
	void load_integer(int id, int ue_id, string column, int& numeric);

	// Функция загрузки символьных значений
	void load_char(int id, int ue_id, string column, string& value);
};

#endif // !SETTINGS
