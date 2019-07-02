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
	rc = sqlite3_open("dataBase.db", &db);
	if (rc)
	{
		fprintf(stderr, "Error in opening database: \n", sqlite3_errmsg(db));
	}
	else
	{
		fprintf(stderr, "Database opened\n");
	}
}

Settings::~Settings()
{
	sqlite3_close(db);
}

void Settings::upd_integer(int id, int ue_id, string column, int numeric)
{
	stringstream commandStream;

	if (ue_id)
	{
		commandStream << "UPDATE User Element" \
					     " SET " << column << " = " << numeric \
					  << " WHERE ID = " << id << "," << " User Element ID = " << ue_id << ";";

		string command(commandStream.str());

		rc = sqlite3_exec(db, command.c_str(), NULL, NULL, NULL);

		if (rc)
		{
			fprintf(stderr, "Error in updating database: \n", sqlite3_errmsg(db));
		}
		else
		{
			fprintf(stderr, "Database was updated\n");
		}
	}
	else
	{
		commandStream << "UPDATE Widgets" \
						 " SET " << column << " = " << numeric \
				      << " WHERE ID = " << id << ";";

		string command(commandStream.str());

		rc = sqlite3_exec(db, command.c_str(), NULL, NULL, NULL);

		if (rc)
		{
			fprintf(stderr, "Error in updating database: \n", sqlite3_errmsg(db));
		}
		else
		{
			fprintf(stderr, "Database was updated\n");
		}
	}
}

void Settings::upd_char(int id, int ue_id, string column, string value)
{
	stringstream commandStream;

	if (ue_id)
	{
		commandStream << "UPDATE User Element" \
						 " SET " << column << " = " << value \
					  << " WHERE ID = " << id << "," << "User Element ID = " << ue_id << ";";

		string command(commandStream.str());

		rc = sqlite3_exec(db, command.c_str(), NULL, NULL, NULL);

		if (rc)
		{
			fprintf(stderr, "Error in updating database: \n", sqlite3_errmsg(db));
		}
		else
		{
			fprintf(stderr, "Database was updated\n");
		}
	}
	else
	{
		commandStream << "UPDATE Widgets" \
						 " SET " << column << " = " << value \
					  << " WHERE ID = " << id << ";";

		string command(commandStream.str());

		rc = sqlite3_exec(db, command.c_str(), NULL, NULL, NULL);

		if (rc)
		{
			fprintf(stderr, "Error in updating database: \n", sqlite3_errmsg(db));
		}
		else
		{
			fprintf(stderr, "Database was updated\n");
		}
	}
}

void Settings::load_integer(int id, int ue_id, string column, int& numeric)
{
	stringstream commandStream;
	sqlite3_stmt* stmt;

	if (ue_id)
	{
		commandStream << "SELECT " << column \
					  << " FROM" << " User Element" \
					   	 " WHERE ID = " << id << ", User Element ID = " << ue_id << ";";

		string command(commandStream.str());

		if (sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, NULL))
		{
			fprintf(stderr, "Error while compiling statement: \n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
		}
		else
		{
			int rc;

			if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
			{
				numeric = sqlite3_column_int(stmt, 0);
			}
		}
	}
	else
	{
		commandStream << "SELECT " << column \
					  << " FROM" << " Widget" \
						 " WHERE ID = " << id << ";";

		string command(commandStream.str());

		if (sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, NULL))
		{
			fprintf(stderr, "Error while compiling statement: \n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
		}
		else
		{
			int rc;

			if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
			{
				numeric = sqlite3_column_int(stmt, 0);
			}
		}
	}
}

void Settings::load_char(int id, int ue_id, string column, string& value)
{
	stringstream commandStream;
	sqlite3_stmt* stmt;

	if (ue_id)
	{
		commandStream << "SELECT " << column \
					  << " FROM" << " User Element" \
						 " WHERE ID = " << id << ", User Element ID = " << ue_id << ";";

		string command(commandStream.str());

		if (sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, NULL))
		{
			fprintf(stderr, "Error while compiling statement: \n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
		}
		else
		{
			int rc;

			if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
			{
				value = sqlite3_column_int(stmt, 0);
			}
		}
	}
	else
	{
		commandStream << "SELECT " << column \
					  << " FROM" << " Widget" \
						 " WHERE ID = " << id << ";";

		string command(commandStream.str());

		if (sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, NULL))
		{
			fprintf(stderr, "Error while compiling statement: \n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
		}
		else
		{
			int rc;

			if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
			{
				value = sqlite3_column_int(stmt, 0);
			}
		}
	}
}
