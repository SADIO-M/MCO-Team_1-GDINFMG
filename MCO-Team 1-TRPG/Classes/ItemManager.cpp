#include "ItemManager.h"

void ItemManager::Update(Connection* connection, Statement* statement)
{
	string input = "-";
	while (input != "0") {

		PrintInputs();

		cout << "\n\n[ ENTER INPUT ] : ";
		cin >> input;

		if (input == "1") { // ADD RECORD
			string itemID, itemName, itemType, cost;

			cout << "\n\nENTER NEW ITEM DETAILS\n    > ENTER [ ITEM ID ] : ";
			cin >> itemID;
			cin.ignore();
			cout << "\n    > ENTER [ ITEM NAME ] (Note: Must format as '<name>') : ";
			getline(cin, itemName);
			cout << "\n    > ENTER [ ITEM TYPE ] (Ex. \'Weapon\'): ";
			getline(cin, itemType);
			cout << "\n    > ENTER [ ITEM COST ] : ";
			cin >> cost;

			try {
				ResultSet* res
					= statement->executeQuery(AddRow(itemID, itemName, itemType, cost));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "2") { // UPDATE RECORD
			string itemID, columnName, newValue;

			cout << "\n\nENTER NEW ITEM DETAILS\n > Note: All strings must be encased in single quotes.\n    > ENTER [ ITEM ID ] : ";
			cin >> itemID;
			cin.ignore();
			cout << "\n    > ENTER [ DATA COLUMN NAME ] (ItemName, ItemName, `type`, cost) : ";
			getline(cin, columnName);
			cout << "\n    > ENTER [ NEW VALUE ] : ";
			getline(cin, newValue);

			try {
				ResultSet* res
					= statement->executeQuery(UpdateRow(itemID, columnName, newValue));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "3") { // DISPLAY ALL CAMPAIGNS
			ResultSet* res
				= statement->executeQuery(ViewAll());

			cout << "ITEM ID | ITEM NAME\n";
			while (res->next()) {
				cout << res->getString("ItemID") << "         "
					<< left << setw(31) << res->getString("ItemName") << endl;
			}
		}

		else if (input == "4") { // DELETE RECORD
			string ItemID;

			cout << "\n\nDELETE ITEM RECORD\n    > ENTER [ ITEM ID ] : ";
			cin >> ItemID;

			try {
				ResultSet* res
					= statement->executeQuery(DeleteFrom(ItemID));
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}

		else if (input == "5") {
			string itemID;

			cout << "\n\nFIND ITEM OWNER";
			ResultSet* res
				= statement->executeQuery(ViewAll());
			cout << "ITEM ID | ITEM NAME\n";
			while (res->next()) {
				cout << res->getString("ItemID") << "         "
					<< left << setw(31) << res->getString("ItemName") << endl;
			}

			cout << "\n    > ENTER [ ITEM ID ] : ";
			cin >> itemID;

			try {
				ResultSet* res
					= statement->executeQuery(SeePlayerOwned(itemID));

				cout << left << setw(25) << "ITEM NAME" << left << setw(31) << "| OWNED BY" << "| AMOUNT\n";
				while (res->next()) {
					cout << left << setw(25) << res->getString("Item") << "  "
						<< left << setw(31) << res->getString("Owned By") << "  "
						<< left << setw(5) << res->getString("Amount") 
						<< endl;
				}
			}
			catch (sql::SQLException e) {
				cout << "\nFeedback: \n" << e.what() << endl;
			}
		}
	}
}

string ItemManager::AddRow(string id, string name, string type, string cost)
{
	string query = "INSERT INTO Item (ItemID, ItemName, `type`, cost) VALUES";
	string query2 = "(" + id + ", " + name + ", " + type + ", " + cost + ")";

	string fullQuery = query + query2;

	return fullQuery;
}

string ItemManager::UpdateRow(string id, string columnName, string newValue)
{
	string query = "UPDATE Item";
	string query2 = "\nSET " + columnName + " = " + newValue;
	string query3 = "\nWHERE ItemID = " + id;

	string fullQuery = query + query2 + query3;

	return fullQuery;
}

string ItemManager::ViewAll()
{
	string query = "SELECT ItemID, ItemName\nFROM Item";

	return query;
}

string ItemManager::DeleteFrom(string id)
{
	string query = "DELETE FROM Item\nWHERE ItemID = " + id;

	return query;
}

string ItemManager::SeePlayerOwned(string itemID)
{
	string query = "SELECT I.itemname AS Item, CONCAT(first_name, \" \", last_name) AS 'Owned By', Inv.quantity as \"Amount\"";
	string query2 = "\nFROM Item AS I JOIN inventory as Inv ON Inv.ItemID = I.ItemID, Characters AS C";
	string query3 = "\nWHERE Inv.CharID = C.CharID AND Inv.ItemID = " + itemID;
	string query4 = "\nORDER BY 2";

	string fullQuery = query + query2 + query3 + query4;

	return fullQuery;
}

// HELPER FUNCTIONS ----------------------------------------------------------------

void ItemManager::PrintInputs()
{
	cout << "\n|| MANAGE ITEMS ||\n	    ITEM MANAGEMENT\n    [1] - Add New Item"
		<< "\n    [2] - Update Item\n    [3] - View All Items"
		<< "\n    [4] - Delete Item\n	    TOOLS\n    [5] - Find Item Owner\n"
		<< "\n    [0] - EXIT";
}

