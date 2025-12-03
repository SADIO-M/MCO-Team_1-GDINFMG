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
			cout << "\n    [1] - This is a Player-Owned Character\n    [2] - This is a NPC\n    > ENTER [ INPUT ] : ";
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
				cout << "\n\n    ENEMY TYPE\n    > [1] - Enemy\n    > [2] - Friendly\n    > ENTER [ INPUT ] : ";
				cin >> type;

				if (type == "1") {
					try {
						ResultSet* res
							= statement->executeQuery(AddRowNPC(CharacterID, "\'enemy\'"));
					}
					catch (sql::SQLException e) {
						cout << "\nFeedback: \n" << e.what() << endl;
					}
				}
				else if (type == "2") {
					try {
						ResultSet* res
							= statement->executeQuery(AddRowNPC(CharacterID, "\'friendly\'"));
					}
					catch (sql::SQLException e) {
						cout << "\nFeedback: \n" << e.what() << endl;
					}
				}
			}
		} 

		else if (input == "3") {
			ResultSet* res
				= statement->executeQuery(ViewAll());

			//Loop through the result set and display data
			int count = 0;
			cout << "CHARACTER ID | CHARACTER NAME\n";
			while (res->next()) {
				cout << res->getString("CharID") << "         "
					<< left << setw(31) << res->getString("Name") << endl;
			}
		}

		else if (input == "4") {
			string CharId;

			cout << "\n\nDELETE CHARACTER RECORD\n    > ENTER [ CHARACTER ID ] : ";
			cin >> CharId;

			input = "";
			cout << "\n    [1] - This is a Player-Owned Character\n    [2] - This is a NPC\n    > ENTER [ INPUT ] : ";
			cin >> input;

			try {
				ResultSet* res
					= statement->executeQuery(DeleteFrom(input, CharId));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}

			try {
				ResultSet* res
					= statement->executeQuery(DeleteFrom("0", CharId));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
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
		query = "UPDATE PlayerCharacter";
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
	string query = "SELECT CharID, CONCAT(first_name, ' ', last_name) AS 'Name'\nFROM Characters\nORDER BY 1;";

	return query;
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

string CharacterManager::DeleteFrom(string type, string id) {

	string query;
	if (type == "1")
		query = "DELETE FROM PlayerCharacter\nWHERE CharID = " + id;
	else if (type == "2")
		query = "DELETE FROM NonPlayableCharacter\nWHERE CharID = " + id;
	else if (type == "0")
		query = "DELETE FROM Characters\nWHERE CharID = " + id;

	return query;
}

// HELPER FUNCTIONS ----------------------------------------------------------------

void CharacterManager::PrintInputs()
{
	cout << "\n|| MANAGE CHARACTERS ||\n    [1] - Add Record"
		<< "\n    [2] - Update Record\n    [3] - View All Records"
		<< "\n    [4] - Delete Record\n	    CAMPAIGN/SESSION MANAGEMENT"
		<< "\n    [5] - Add Player to Campaign\n    [6] - Remove Player from Campaign"
		<< "\n    [7] - Add Player to Session\n    [8] - Remove Player from Session"
		<< "\n    [0] - EXIT";
}