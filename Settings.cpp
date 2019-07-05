#include "Settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;
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

void Settings::upd_value(int id, string widgetElement, string column, string value)
{
	stringstream commandStream;

	// Updating User Element
	if (widgetElement.empty() == false)
	{
		commandStream << "UPDATE USER_ELEMENT" \
			" SET " << column << " = " << value \
			<< " WHERE WidgetID = " << id << "," << "UserElementName = " << widgetElement << ";";
	}
	// Updating Widget
	else
	{
		commandStream << "UPDATE WIDGET" \
			" SET " << column << " = " << value \
			<< " WHERE ID = " << id << ";";
	}

	string command(commandStream.str());

	// Execution of statement
	int rc = sqlite3_exec(db, command.c_str(), NULL, NULL, NULL);

	if (rc)
	{
		// In case of error
		fprintf(stderr, "Error in updating database: \n", sqlite3_errmsg(db));
		return;
	}
	// Operation done successfully
	fprintf(stderr, "Database was updated\n");
}

void Settings::load_value(int id, string widgetElement, string column, string& value, int numeric)
{
	stringstream commandStream;
	sqlite3_stmt* stmt;

	// Load from User Element
	if (widgetElement.empty() == false)
	{
		commandStream << "SELECT " << column \
			<< " FROM USER_ELEMENT" \
			" WHERE WidgetID = " << id << ", UserElementName = " << widgetElement << ";";
	}
	// Load from Widget
	else
	{
		commandStream << "SELECT " << column \
			<< " FROM" << " WIDGET" \
			" WHERE ID = " << id << ";";
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
				value = to_string(sqlite3_column_int(stmt, 0));
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

void Settings::load_size(int id, string widgetElement, int& x, int& y, int& width, int& lenght)
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

void Settings::upd_size(int id, string widgetElement, int x, int y, int width, int lenght)
{
	string value;

	value = to_string(x);
	upd_value(id, widgetElement, "CoordinateX", value);

	value = to_string(y);
	upd_value(id, widgetElement, "CoordinateY", value);

	value = to_string(width);
	upd_value(id, widgetElement, "Width", value);

	value = to_string(lenght);
	upd_value(id, widgetElement, "Lenght", value);
}
