#include "SessionManager.h"

SessionManager::SessionManager(UserManager* user)
{
	this->user = user;
}

void SessionManager::Update(Connection* connection, Statement* statement)
{
	string input = "-";
	while (input != "0") {

		PrintInputs();

		cout << "\n\n[ ENTER INPUT ] : ";
		cin >> input;

		if (input == "1") {
			string SessionId, CampaignId, SessionDate, SessionDuration;

			cout << "\n\nENTER NEW SESSION DETAILS\n    > ENTER [ SESSION ID ] : ";
			cin >> SessionId;
			cin.ignore();
			cout << "\nSELECT CAMPAIGN WHERE THE SESSION OCCURED\n";
			GetCampaign(statement);
			cout << "\n    > ENTER [ CAMPAIGN ID ]: ";
			cin >> CampaignId;
			cin.ignore();
			cout << "\n    > ENTER [ SESSION DATE ] (Note: Must In 'YYYY-MM-DD' Format): ";
			getline(cin, SessionDate);
			cout << "\n    > ENTER [ SESSION DURATION ] (Note: Must In 'hh:mm:ss.nn' Format): ";
			getline(cin, SessionDuration);

			try {
				ResultSet* res
					= statement->executeQuery(AddRow(SessionId, SessionDate, SessionDuration, CampaignId));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}
		if (input == "2") {
			string SessionID, columnName, newValue;

			cout << "\n\nENTER NEW SESSION DETAILS\n    > ENTER [ SESSION ID ] : ";
			cin >> SessionID;
			cin.ignore();
			cout << "\n    > ENTER [ DATA COLUMN NAME ] (SessionDate, SessionDuration) : ";
			getline(cin, columnName);
			if (columnName == "SessionDate") cout << "\n FORMAT: 'YYY-MM-DD'";
			else if (columnName == "SessionDuration") cout << "\n FORMAT: 'hh:mm:ss.nn'";
			cout << "\n    > ENTER [ NEW VALUE ] : ";
			getline(cin, newValue);

			try {
				ResultSet* res
					= statement->executeQuery(UpdateRow(SessionID, columnName, newValue));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}
		else if (input == "3") {
			ResultSet* res
				= statement->executeQuery(ViewAll());

			//Loop through the result set and display data
			int count = 0;
			cout << "SESSION ID | SESSION DATE | SESSION DURATION\n";
			while (res->next()) {
				cout << res->getString("SessionID") << "         "
					<< left << setw(31) << res->getString("SessionDate")
					<< res->getString("SessionDuration") << endl;
			}
		}
		else if (input == "4") {
			string SessionID;

			cout << "\n\nDELETE SESSION DETAILS\n    > ENTER [ SESSION ID ] : ";
			cin >> SessionID;

			try {
				ResultSet* res
					= statement->executeQuery(DeleteFrom(SessionID));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}
		else if (input == "5") {
			string CampaignID;

			cout << "\n\nSELECT CAMPAIGN TO CHECK ITS LATEST SESSION\n";
			GetCampaign(statement);
			cout << "\nENTER [ Campaign ID ] : ";
			cin >> CampaignID;
			
			ResultSet* res
				= statement->executeQuery(CheckRecent(CampaignID));

			cout <<"\nLATEST SESSION IN THE SELECTED CAMPAIGN\n";
			if (res->next()) {
				cout << res->getString("MAX(SessionDate)") << endl;
			}
			else cout << "No Available Result Due To Campaign Not Having A Session Yet.\n";
		}

		else if (input == "6") {
			string sessionID;

			cout << "\n\nREVIEW SESSION\n    > ENTER [ SESSION ID ] : ";
			cin >> sessionID;

			try {
				ResultSet* res
					= statement->executeQuery(ReviewSession(sessionID));
				
				while (res->next()) {
					cout << "Event: " << res->getString("Event") << endl;
				}
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}
	}
}

string SessionManager::AddRow(string sessionID, string sessionDate, string sessionDuration, string campaignID)
{
	string query = "INSERT INTO Sessions (SessionID, SessionDate, SessionDuration, CampaignID) VALUES";
	string query2 = "(" + sessionID + ", " + sessionDate + ", " + sessionDuration + ", " + campaignID + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string SessionManager::UpdateRow(string id, string columnName, string newValue)
{
	string query = "UPDATE Sessions";
	string query2 = "\nSET " + columnName + " = " + newValue;
	string query3 = "\nWHERE SessionID = " + id;

	string fullQuery = query + query2 + query3;

	return fullQuery;
}

string SessionManager::ViewAll()
{
	string query = "SELECT SessionID, SessionDate, SessionDuration\nFROM Sessions";

	return query;
}

string SessionManager::DeleteFrom(string id)
{
	string query = "DELETE FROM Sessions\nWHERE SessionID = " + id;

	return query;
}

void SessionManager::GetCampaign(Statement* statement) {
	CampaignManager Campaign;
	ResultSet* res
		= statement->executeQuery(Campaign.ViewAll());

	//Loop through the result set and display data
	int count = 0;
	cout << "CAMPAIGN ID | CAMPAIGN NAME\n";
	while (res->next()) {
		cout << res->getString("CampaignID") << "         "
			<< left << setw(31) << res->getString("CampaignName") << endl;
	}

}

string SessionManager::CheckRecent(string id) {
	string query = "SELECT MAX(SessionDate)\nFROM Sessions\nWhere CampaignID = " + id;

	return query;
}

string SessionManager::ReviewSession(string sessionID)
{
	string query = "SELECT descriptions as Event\nFROM ImportantNarrativePoint\nWhere SessionID = " + sessionID;

	return query;
}

// HELPER FUNCTIONS ----------------------------------------------------------------

void SessionManager::PrintInputs()
{
	cout << "\n|| MANAGE SESSIONS ||\n    [1] - Add Record"
		<< "\n    [2] - Update Record\n    [3] - View All Records"
		<< "\n    [4] - Delete Record\n    [5] - View Most Recent Session From A Campaign"
		<< "\n    [6] - Review Session\n"
		<< "\n    [0] - EXIT";
}


