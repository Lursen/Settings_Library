#ifndef SETTINGS_H
#define SETTINGS_H
#include <QtWidgets>
#include <string>
#include "sqlite3.h"

class Settings
{
	sqlite3* db;

public:

	Settings();

	~Settings();

	// Method for updating value in database
	void upd_value(std::string id, std::string widgetElement, std::string column, std::string value, int numeric);

	// Method for loading value from database
	void load_value(std::string id, std::string widgetElement, std::string column, std::string& value, int numeric);

	// Method for loading size of widget/user element from database
	void load_size(std::string id, std::string widgetElement, int& x, int& y, int& width, int& lenght);

	// Method for updating size of widget/user element in database
	void upd_size(std::string id, std::string widgetElement, int x, int y, int width, int lenght);

	// Method for updating data for widget in database
	void upd_widget(QWidget* widget);

	// Method for loading widget data from database
	void load_widget(QWidget* widget, std::string& parent);

	// Method for updating user element data in database
	void upd_uelement(QWidget* userElement, std::string value);

	// Method for loading user element data from database
	void load_uelement(QWidget* userElement, std::string& value);
};

#endif // !SETTINGS