#pragma once

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "CampaignManager.h"

using namespace std;
using namespace sql;

class SessionManager {
public:
	void Update(Connection* connection, Statement* statement);
	string AddRow(string sessionID, string sessionDate, string sessionDuration, string campaignID);
	string UpdateRow(string id, string columnName, string newValue);
	string ViewAll();
	string DeleteFrom(string id);
	void GetCampaign(Statement* statement);
	string CheckRecent(string campaignID);
private:
	/*void PrintInputs();*/
};
