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
	int rc = sqlite3_open("dataBase.db", &db);
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
	sqlite3_close(db);
}

void Settings::upd_value(int id, int ue_id, string column, string value)
{
	stringstream commandStream;

	// Updating User Element
	if (ue_id)
	{
		commandStream << "UPDATE User Element" \
						 " SET " << column << " = " << value \
					  << " WHERE ID = " << id << "," << "User Element ID = " << ue_id << ";";
	}
	// Updating Widget
	else
	{
		commandStream << "UPDATE Widgets" \
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
	}
	else
	{
		// Operation done successfully
		fprintf(stderr, "Database was updated\n");
	}
}

void Settings::load_value(int id, int ue_id, string column, string& value, int numeric)
{
	stringstream commandStream;
	sqlite3_stmt* stmt;

	// Load from User Element
	if (ue_id)
	{
		commandStream << "SELECT " << column \
			<< " FROM User Element" \
			" WHERE ID = " << id << ", User Element ID = " << ue_id << ";";
	}
	// Load fron Widget
	else
	{
		commandStream << "SELECT " << column \
			<< " FROM" << " Widget" \
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
	}
	else
	{
		// Evaluation of statement
		rc = sqlite3_step(stmt);

		if (rc == SQLITE_ROW)
		{
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
		}
		// Destruction of statement
		sqlite3_finalize(stmt);
	}
}
