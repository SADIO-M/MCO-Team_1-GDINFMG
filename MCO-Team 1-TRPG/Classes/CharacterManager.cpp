#include "CharacterManager.h"

void CharacterManager::Update(Connection* connection, Statement* statement) {
	string input = "-";
	while (input != "0") {

		PrintInputs();

		cout << "\n\n[ ENTER INPUT ] : ";
		cin >> input;

		if (input == "1") { 
			string CharacterID, CharacterFirstName, CharacterLastName, attackID, initiative;

			cout << "\n\nENTER NEW CHARACTER DETAILS\n    > ENTER [ CHARACTER ID ] : ";
			cin >> CharacterID;
			cin.ignore();
			cout << "\n    > ENTER [ CHARACTER FIRST NAME ] (Note: Must format as '<name>') : ";
			getline(cin, CharacterFirstName);
			cout << "\n    > ENTER [ CHARACTER LAST NAME ] (Note: Must format as '<name>') : ";
			getline(cin, CharacterLastName);
			cout << "\n    > ENTER [ CHARACTER ATTACK ID ] : ";
			cin >> attackID;
			cout << "\n    > ENTER [ CHARACTER INITIATIVE ] : ";
			cin >> initiative;

			try {
				ResultSet* res
					= statement->executeQuery(AddRow(CharacterID, CharacterFirstName, CharacterLastName, attackID, initiative));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}

			input = "";
			cout << "\n    [1] - This is a Player-Owned Character\n    [2] - This is a NPC";
			cin >> input;

			if (input == "1") {
				string playerID;
				cout << "\n\n    > ENTER [ PLAYER ID OF OWNER ] : ";
				cin >> playerID;

				try {
					ResultSet* res
						= statement->executeQuery(AddRowPC(CharacterID, playerID));
				}
				catch (sql::SQLException e) {
					cout << "\nFeedback: \n" << e.what() << endl;
				}
			}
			else if (input == "2") {
				string type;
				cout << "\n\n    > ENTER [ PLAYER ID OF OWNER ] : ";
			}
		}

	}
}

string CharacterManager::AddRow(string id, string firstName, string lastName, string attackID, string initiative) {
	string query = "INSERT INTO Characters (CharID, first_name, last_name, AttackID, Initiative) VALUES";
	string query2 = "(" + id + ", " + firstName + ", " + lastName + ", " + attackID + ", " + initiative + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string CharacterManager::AddRowPC(string id, string playerID) {
	string query = "INSERT INTO PlayerCharacter (CharID, DeathSavesSuccess, DeathSavesFails, PlayerID) VALUES";
	string query2 = "(" + id + ", 0, 0, " + playerID + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string CharacterManager::AddRowNPC(string id, string type) {
	string query = "INSERT INTO NonPlayableCharacter (CharID, `type`) VALUES";
	string query2 = "(" + id + ", " + type + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string CharacterManager::UpdateRow(string type, string id, string columnName, string newValue) {
	
	string query;
	if (type == "1") {
		query = "UPDATE Characters";
	}
	else if (type == "2") {
		query = "UPDATE Player";
	}
	else if (type == "3") {
		query = "UPDATE NonPlayableCharacter";
	}
 
	string query2 = "\nSET " + columnName + " = " + newValue;
	string query3 = "\nWHERE CharID = " + id;

	string fullQuery = query + query2 + query3;

	return fullQuery;
}

string CharacterManager::ViewAll() {

}

string CharacterManager::AddToCampaign(string id, string campaignID)
{
	return string();
}

string CharacterManager::RemoveFromCampaign(string id, string campaignID)
{
	return string();
}

string CharacterManager::AddToSession(string id, string sessionID)
{
	return string();
}

string CharacterManager::RemoveFromSession(string id, string sessionID)
{
	return string();
}

string CharacterManager::DeleteFrom(string id) {

}

// HELPER FUNCTIONS ----------------------------------------------------------------

void CharacterManager::PrintInputs()
{
	cout << "\n|| MANAGE CAMPAIGNS ||\n    [1] - Add Record"
		<< "\n    [2] - Update Record\n    [3] - View All Records"
		<< "\n    [4] - Delete Record\n	        CAMPAIGN/SESSION MANAGEMENT"
		<< "\n    [4] -Add Player to Campaign\n    [5] - Remove Player from Campaign"
		<< "\n    [4] -Add Player to Session\n    [5] - Remove Player from Session"
		<< "\n    [0] - EXIT";
}