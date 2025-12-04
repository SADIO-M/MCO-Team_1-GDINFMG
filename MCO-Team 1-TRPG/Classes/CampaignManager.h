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

#include "UserManager.h"

class CampaignManager {
	public:
		UserManager* user;
		CampaignManager();
		CampaignManager(UserManager* user);

		void Update(Connection* connection, Statement* statement);
		string AddRow(string id, string name, string ruleSystemID);
		string UpdateRow(string id, string columnName, string newValue);
		string ViewAll();
		string DeleteFrom(string id);

		string GetCampaignFromGM();
		string CheckPlayerCampaign(string id);
	private: 
		void PrintInputs();
};
