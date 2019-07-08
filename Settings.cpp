#include "Settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using std::string;
using std::stringstream;

Settings::Settings()
{
	// Opening database connection
	int rc = sqlite3_open("Settings.db", &db);
	if (rc)
	{
		// In case of error
		fprintf(stderr, "Error in opening database: \n", sqlite3_errmsg(db));
	}
	else
	{
		// Successful opening
		fprintf(stderr, "Database opened\n");
	}
}

Settings::~Settings()
{
	// Closing database connection
	fprintf(stderr, "Database closed\n");
	sqlite3_close(db);
}

void Settings::upd_value(string id, string widgetElement, string column, string value, int numeric)
{
	stringstream commandStream;

	// Updating User Element
	if (numeric)
	{
		if (widgetElement.empty() == false)
		{
			commandStream << "UPDATE USER_ELEMENT" \
				" SET " << column << " = " << value \
				<< " WHERE WidgetID = \"" << id << "\"," << "UserElementName = \"" << widgetElement << "\";";
		}
		// Updating Widget
		else
		{
			commandStream << "UPDATE WIDGET" \
				" SET " << column << " = " << value \
				<< " WHERE ID = \"" << id << "\";";
		}
	}
	else
	{
		if (widgetElement.empty() == false)
		{
			commandStream << "UPDATE USER_ELEMENT" \
				" SET " << column << " = \"" << value << "\"" \
				<< " WHERE WidgetID = \"" << id << "\"," << "UserElementName = \"" << widgetElement << "\";";
		}
		// Updating Widget
		else
		{
			commandStream << "UPDATE WIDGET" \
				" SET " << column << " = \"" << value << "\""\
				<< " WHERE ID = \"" << id << "\";";
		}
	}
	string command(commandStream.str());

	// Execution of statement
	int rc = sqlite3_exec(db, command.c_str(), NULL, NULL, NULL);
	fprintf(stderr, command.c_str());

	if (rc)
	{
		// In case of error
		fprintf(stderr, "Error in updating database: \n", sqlite3_errmsg(db));
		return;
	}
	// Operation done successfully
	fprintf(stderr, "Database was updated\n");
}

void Settings::load_value(string id, string widgetElement, string column, string& value, int numeric)
{
	stringstream commandStream;
	sqlite3_stmt* stmt;

	// Load from User Element
	if (numeric)
	{
		if (widgetElement.empty() == false)
		{
			commandStream << "SELECT " << column \
				<< " FROM USER_ELEMENT" \
				<< " WHERE WidgetID = \"" << id << "\"," << "UserElementName = \"" << widgetElement << "\";";
		}
		// Load from Widget
		else
		{
			commandStream << "SELECT " << column \
				<< " FROM" << " WIDGET" \
				<< " WHERE ID = \"" << id << "\";";
		}
	}
	else
	{
		if (widgetElement.empty() == false)
		{
			commandStream << "SELECT " << column \
				<< " FROM USER_ELEMENT" \
				<< " WHERE WidgetID = \"" << id << "\"," << "UserElementName = \"" << widgetElement << "\";";
		}
		// Load from Widget
		else
		{
			commandStream << "SELECT " << column \
				<< " FROM" << " WIDGET" \
				<< " WHERE ID = \"" << id << "\";";
		}
	}
	string command(commandStream.str());

	// Preparation of statement
	int rc = sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, NULL);

	if (rc)
	{
		// In case of error
		fprintf(stderr, "Error while compiling statement: \n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return;
	}
	fprintf(stderr, "Compiling successful\n");
	// Evaluation of statement

	bool done = false;
	while (!done)
	{
		switch (sqlite3_step(stmt))
		{
		case (SQLITE_ROW):
			fprintf(stderr, "Row found\n");
			// If value in database is numeric
			if (numeric)
			{
				value = std::to_string(sqlite3_column_int(stmt, 0));
			}
			// If value in database is symbolic
			else
			{
				string str(reinterpret_cast<char const*>(sqlite3_column_text(stmt, 0)), 100);
				value = str;
			}
			break;

		case (SQLITE_DONE):
			fprintf(stderr, "Step done\n");
			done = true;
			break;

		default:
			fprintf(stderr, "Failed\n");
			break;
		}
	}
	// Destruction of statement
	sqlite3_finalize(stmt);
}

void Settings::load_size(string id, string widgetElement, int& x, int& y, int& width, int& lenght)
{
	string value;

	load_value(id, widgetElement, "CoordinateX", value, 1);
	x = stoi(value);

	load_value(id, widgetElement, "CoordinateY", value, 1);
	y = stoi(value);

	load_value(id, widgetElement, "Width", value, 1);
	width = stoi(value);

	load_value(id, widgetElement, "Lenght", value, 1);
	lenght = stoi(value);
}

void Settings::upd_size(string id, string widgetElement, int x, int y, int width, int lenght)
{
	string value;

	value = std::to_string(x);
	upd_value(id, widgetElement, "CoordinateX", value, 1);

	value = std::to_string(y);
	upd_value(id, widgetElement, "CoordinateY", value, 1);

	value = std::to_string(width);
	upd_value(id, widgetElement, "Width", value, 1);

	value = std::to_string(lenght);
	upd_value(id, widgetElement, "Lenght", value, 1);
}

void Settings::upd_widget(QWidget* widget)
{
	string id = widget->objectName().toStdString();
	int x = widget->x();
	int y = widget->y();
	int width = widget->width();
	int lenght = widget->height();

	upd_size(id, "", x, y, width, lenght);
	if (widget->parentWidget() != nullptr)
	{
		upd_value(id, "", "Parent", widget->parentWidget()->objectName().toStdString(), 0);
	}
}

void Settings::load_widget(QWidget* widget, string& parent)
{
	string id = widget->objectName().toStdString();
	int x, y, width, lenght;

	load_size(id, "", x, y, width, lenght);
	load_value(id, "", "Parent", parent, 0);

	QRect widgetSize(x, y, width, lenght);
	widget->setGeometry(widgetSize);
}

void Settings::upd_uelement(QWidget* userElement, string value)
{
	string widgetID = userElement->parentWidget()->objectName().toStdString();
	string widgetElement = userElement->objectName().toStdString();
	int x = userElement->x();
	int y = userElement->y();
	int width = userElement->width();
	int lenght = userElement->height();

	upd_size(widgetID, widgetElement, x, y, width, lenght);
	upd_value(widgetID, widgetElement, "Value", value, 0);
}

void Settings::load_uelement(QWidget* userElement, string& value)
{
	string widgetID = userElement->parentWidget()->objectName().toStdString();
	string widgetElement = userElement->objectName().toStdString();
	int x, y, width, lenght;

	load_size(widgetID, widgetElement, x, y, width, lenght);
	load_value(widgetID, widgetElement, "Value", value, 0);

	QRect ueSize(x, y, width, lenght);
	userElement->setGeometry(ueSize);
}
