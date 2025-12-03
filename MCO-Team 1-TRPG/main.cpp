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
#include "Classes/UserManager.h"

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
    SessionManager Sessions;
    CharacterManager Characters;
    UserManager Users;

    statement = connection->createStatement();

    string input = "-";
    while (input != "0"){
        cout << "\nPress 1 to view Campaign Manager";
        cout << "\nPress 2 to view Session Manager";
        cout << "\nPress 3 to view Character Manager";
        cout << "\nPress 4 to view User Manager\n\n";
        cout << "[ ENTER INPUT ] : ";
        cin >> input;

        if (input == "1") {
            Campaigns.Update(connection, statement);
        }

        if (input == "2") {
            Sessions.Update(connection, statement);
        }

        if (input == "3") {
            Characters.Update(connection, statement);
        }

        if (input == "4") {
            Users.Update(connection, statement);
        }

        else if (input == "0") {
            break;
        }
    }

    cout << "\n\nApplication closed. Thank you!\n";
    delete statement;
    delete connection;
    system("pause");
    return 0;
}
