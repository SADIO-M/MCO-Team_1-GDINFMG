#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

#include "Classes/CampaignManager.h"
#include "Classes/SessionManager.h"
#include "Classes/CharacterManager.h"

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
//const string password = "HuW@yD0SQL?";

int main()
{
    sql::Driver* driver;
    sql::Connection* connection;
    sql::Statement* statement;
    sql::PreparedStatement* prepStatement;

    string password;
    cout << "Enter server password: ";
    cin >> password;

    //string password = "GOLDeater!1231";

    try
    {
        driver = get_driver_instance();
        connection = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    // INITIALIZATION
    connection->setSchema("CampaignManager");
    CampaignManager Campaigns;

    statement = connection->createStatement();

    string input = "-";
    while (input != "0"){
        cout << "\nPress 1 to view campaign manager\n";
        cout << "\nPress 2 to view session manager\n";
        cout << "[ ENTER INPUT ] : ";
        cin >> input;

        if (input == "1") {
            Campaigns.Update(connection, statement);
        }

        if (input == "2") {
            cout << "INSERT SESSION MANAGER HERE";
        }

        else if (input == "0") {
            break;
        }

        else {
            cout << "\nCommand not recoginized! Try again.\n";
        }
    }

    cout << "\n\nApplication closed. Thank you!\n";
    delete statement;
    delete connection;
    system("pause");
    return 0;
}
