#pragma once

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

class UserManager {
public:
	string UserID;

	void Update(Connection* connection, Statement* statement);
	string AddRow(string id, string firstName, string lastName);
	string UpdateRow(string id, string columnName, string newValue);
	string ViewAll();
	string DeleteFrom(string id);

	string AddToCampaign(string id, string campaignID);
	string RemoveFromCampaign(string id, string campaignID);
	string AddToSession(string id, string sessionID);
	string RemoveFromSession(string id, string sessionID);
private:
	void PrintInputs();
};