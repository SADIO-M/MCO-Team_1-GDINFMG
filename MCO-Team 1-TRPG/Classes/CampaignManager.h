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

// TEMP
const string GameMasterID = "50001";

class CampaignManager {
	public:
		void Update(Connection* connection, Statement* statement);
		string AddRow(string id, string name, string ruleSystemID);
		string UpdateRow(string id, string columnName, string newValue);
		string ViewAll();
		//string DeleteFrom();
		//string GetCampaignFromGM(int GamemasterID);
	private: 
		void PrintInputs();
};
