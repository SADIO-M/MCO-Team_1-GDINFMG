#include "CampaignManager.h"

CampaignManager::CampaignManager(){}

CampaignManager::CampaignManager(UserManager* user)
{
	this->user = user;
}

void CampaignManager::Update(Connection* connection, Statement* statement)
{
	string input = "-";
	while (input != "0") {

		PrintInputs();

		cout << "\n\n[ ENTER INPUT ] : ";
		cin >> input;

		if (input == "1") { // ADD RECORD
			string CampaignId, CampaignName, RuleSystem;

			cout << "\n\nENTER NEW CAMPAIGN DETAILS\n    > ENTER [ CAMPAIGN ID ] : ";
			cin >> CampaignId;
			cin.ignore();
			cout << "\n    > ENTER [ CAMPAIGN NAME ] (Note: Must format as '<name>') : ";
			getline(cin, CampaignName);
			cout << "\n    > ENTER [ RULE SYSTEM ] : ";
			cin >> RuleSystem;

			try {
			ResultSet* res
				= statement->executeQuery(AddRow(CampaignId, CampaignName, RuleSystem));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "2") { // UPDATE RECORD
			string CampaignId, columnName, newValue;

			cout << "\n\nENTER NEW CAMPAIGN DETAILS\n > Note: All strings must be encased in single quotes.\n    > ENTER [ CAMPAIGN ID ] : ";
			cin >> CampaignId;
			cin.ignore();
			cout << "\n    > ENTER [ DATA COLUMN NAME ] (CampaignName, GameMasterID, RuleSystemID) : ";
			getline(cin, columnName);
			cout << "\n    > ENTER [ NEW VALUE ] : ";
			getline(cin, newValue);

			try {
			ResultSet* res
				= statement->executeQuery(UpdateRow(CampaignId, columnName, newValue));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "3") { // DISPLAY ALL CAMPAIGNS
			ResultSet* res
				= statement->executeQuery(ViewAll());

			 //Loop through the result set and display data
			int count = 0;
			cout << "CAMPAIGN ID | CAMPAIGN NAME\n";
			while (res->next()) {
				cout << res->getString("CampaignID") << "         "
					<< left << setw(31) << res->getString("CampaignName") << endl;
			}
		}

		else if (input == "4") { // DELETE RECORD
			string CampaignId;

			cout << "\n\nDELETE CAMPAIGN RECORD\n    > ENTER [ CAMPAIGN ID ] : ";
			cin >> CampaignId;

			try {
				ResultSet* res
					= statement->executeQuery(DeleteFrom(CampaignId));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "5") { // DISPLAY OWNED CAMPAIGNS
			ResultSet* res
				= statement->executeQuery(GetCampaignFromGM());

			//Loop through the result set and display data
			int count = 0;
			cout << "CAMPAIGN ID | CAMPAIGN NAME\n";
			while (res->next()) {
				cout << res->getString("CampaignID") << "         "
					<< left << setw(31) << res->getString("CampaignName") << endl;
			}
		}

		else if (input == "6") { // DISPLAY PLAYER CAMPAIGNS
			string playerID;

			cout << "\n\nDISPLAY PLAYER CAMPAIGNS\n    > ENTER [ PLAYER ID ] : ";
			cin >> playerID;

			ResultSet* res
				= statement->executeQuery(CheckPlayerCampaign(playerID));

			//Loop through the result set and display data
			int count = 0;
			cout << "CAMPAIGN NAME\n";
			while (res->next()) {
				cout << res->getString("CampaignName") << endl;
			}
		}
	}
}

string CampaignManager::AddRow(string id, string name, string ruleSystemID)
{
	string query = "INSERT INTO Campaign (CampaignID, CampaignName, GameMasterID, RuleSystemID) VALUES";
	string query2 = "(" + id + ", " + name + ", " + user->UserID + ", " + ruleSystemID + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string CampaignManager::UpdateRow(string id, string columnName, string newValue)
{
	string query = "UPDATE Campaign";
	string query2 = "\nSET " + columnName + " = " + newValue;
	string query3 = "\nWHERE CampaignID = " + id;

	string fullQuery = query + query2 + query3;

	return fullQuery;
}

string CampaignManager::ViewAll()
{
	string query = "SELECT CampaignID, CampaignName\nFROM Campaign";

	return query;
}

string CampaignManager::DeleteFrom(string id)
{
	string query = "DELETE FROM Campaign\nWHERE CampaignID = " + id;

	return query;
}

string CampaignManager::GetCampaignFromGM()
{
	string query = "SELECT C.CampaignID, C.CampaignName\nFROM Campaign AS C\nWHERE C.GameMasterID = " + user->UserID;

	return query;
}

string CampaignManager::CheckPlayerCampaign(string id)
{
	string query = "SELECT C.CampaignName\nFROM Campaign AS C\nJOIN PlayerCampaign PC ON C.CampaignID = PC.CampaignID\nWhere PC.PlayerID = " + id;

	return query;
}

// HELPER FUNCTIONS ----------------------------------------------------------------

void CampaignManager::PrintInputs()
{
	cout << "\n|| MANAGE CAMPAIGNS ||\n    [1] - Add Record"
		<< "\n    [2] - Update Record\n    [3] - View All Records"
		<< "\n    [4] - Delete Record\n    [5] - List Owned Campaigns"
		<< "\n    [6] - List a Player's Campaigns"
		<< "\n    [0] - EXIT";
}


