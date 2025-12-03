#include "UserManager.h"

void UserManager::Update(Connection* connection, Statement* statement) {

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
			string playerID, columnName, newValue;

			cout << "\n\nENTER NEW PLAYER DETAILS\n    > ENTER [ PLAYER ID ] : ";
			cin >> playerID;
			cin.ignore();
			cout << "\n    > ENTER [ DATA COLUMN NAME ] (PlayerID, first_name, last_name) : ";
			getline(cin, columnName);
			cout << "\n    > ENTER [ NEW VALUE ] : ";
			getline(cin, newValue);

			try {
				ResultSet* res
					= statement->executeQuery(UpdateRow(playerID, columnName, newValue));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "3") { // DISPLAY ALL PLAYERS
			ResultSet* res
				= statement->executeQuery(ViewAll());

			int count = 0;
			cout << "PLAYER ID | NAME\n";
			while (res->next()) {
				cout << res->getString("PlayerID") << "         "
					<< left << setw(31) << res->getString("Name") << endl;
			}
		}

		else if (input == "4") { // DELETE RECORD
			string playerID;

			cout << "\n\nDELETE PLAYER RECORD\n    > ENTER [ PLAYER ID ] : ";
			cin >> playerID;

			try {
				ResultSet* res
					= statement->executeQuery(DeleteFrom(playerID));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "5") {
			string playerID, campaignID;
			cout << "\n\nADDING PLAYER TO CAMPAIGN\n    > ENTER [ PLAYER ID ] : ";
			cin >> playerID;
			cout << "    > ENTER [ CAMPAIGN ID ] : ";
			cin >> campaignID;

			try {
				ResultSet* res
					= statement->executeQuery(AddToCampaign(playerID, campaignID));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "6") {
			string playerID, campaignID;
			cout << "\n\nREMOVING PLAYER FROM CAMPAIGN\n    > ENTER [ PLAYER ID ] : ";
			cin >> playerID;
			cout << "    > ENTER [ CAMPAIGN ID ] : ";
			cin >> campaignID;

			try {
				ResultSet* res
					= statement->executeQuery(RemoveFromCampaign(playerID, campaignID));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "7") {
			string playerID, sessionID;
			cout << "\n\nADDING PLAYER TO SESSION\n    > ENTER [ PLAYER ID ] : ";
			cin >> playerID;
			cout << "    > ENTER [ CAMPAIGN ID ] : ";
			cin >> sessionID;

			try {
				ResultSet* res
					= statement->executeQuery(AddToSession(playerID, sessionID));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "8") {
			string playerID, sessionID;
			cout << "\n\nREMOVING PLAYER FROM SESSION\n    > ENTER [ PLAYER ID ] : ";
			cin >> playerID;
			cout << "    > ENTER [ CAMPAIGN ID ] : ";
			cin >> sessionID;

			try {
				ResultSet* res
					= statement->executeQuery(RemoveFromSession(playerID, sessionID));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}
	}
}

string UserManager::AddRow(string id, string firstName, string lastName) {
	string query = "INSERT INTO Player (PlayerID, first_name, last_name) VALUES";
	string query2 = "(" + id + ", " + firstName + ", " + lastName + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string UserManager::UpdateRow(string id, string columnName, string newValue)
{
	string query = "UPDATE Player";
	string query2 = "\nSET " + columnName + " = " + newValue;
	string query3 = "\nWHERE PlayerID = " + id;

	string fullQuery = query + query2 + query3;

	return fullQuery;
}

string UserManager::ViewAll()
{
	string query = "SELECT PlayerID, CONCAT(first_name, ' ', last_name) AS 'Name'\nFROM Player\nORDER BY 1; ";

	return query;
}

string UserManager::DeleteFrom(string id)
{
	string query = "DELETE FROM Player\nWHERE PlayerID = " + id;

	return query;
}

string UserManager::AddToCampaign(string id, string campaignID)
{
	string query = "INSERT INTO PlayerCampaign (PlayerID, CampaignID) VALUES";
	string query2 = "(" + id + ", " + campaignID + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string UserManager::RemoveFromCampaign(string id, string campaignID)
{
	string query = "DELETE FROM PlayerCampaign";
	string query2 = "\nWHERE PlayerID = " + id + " AND CampaignID = " + campaignID;

	string fullQuery = query + query2;

	return fullQuery;
}

string UserManager::AddToSession(string id, string sessionID)
{
	string query = "INSERT INTO PlayerSessionAttended (PlayerID, SessionID) VALUES";
	string query2 = "(" + id + ", " + sessionID + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string UserManager::RemoveFromSession(string id, string sessionID)
{
	string query = "DELETE FROM PlayerSessionAttended";
	string query2 = "\nWHERE PlayerID = " + id + " AND SessionID = " + sessionID;

	string fullQuery = query + query2;

	return fullQuery;
}

// HELPER FUNCTIONS ----------------------------------------------------------------

void UserManager::PrintInputs()
{
	cout << "\n|| MANAGE PLAYERS ||\n	    PLAYER MANAGEMENT\n    [1] - Add Record"
		<< "\n    [2] - Update Record\n    [3] - View All Player Records"
		<< "\n    [4] - Delete Record\n	    CAMPAIGN/SESSION MANAGEMENT"
		<< "\n    [5] - Add Player to Campaign\n    [6] - Remove Player from Campaign"
		<< "\n    [7] - Add Player to Session\n    [8] - Remove Player from Session"
		<< "\n    [0] - EXIT";
}