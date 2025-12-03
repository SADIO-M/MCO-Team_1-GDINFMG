#pragma once

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;
using namespace sql;

#include "CampaignManager.h"

class CharacterManager {
public:
	void Update(Connection* connection, Statement* statement);
	string AddRow(string id, string firstName, string lastName, string attackID, string initiative);
	string AddRowPC(string id, string playerID);
	string AddRowNPC(string id, string type);
	string UpdateRow(string type, string id, string columnName, string newValue);
	string ViewAll();
	string DeleteFrom(string type, string id);

	string GetBackground(string id);
private:
	void PrintInputs();
};