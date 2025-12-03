// SAMPLE CODE IN MAIN
#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "HuW@yD0SQL?";

int main()
{
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;

    //string password;
    //cout << "Enter server password: ";
    //cin >> password;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    //please create database "quickstartdb" ahead of time
    con->setSchema("concert");

    char input = '-';
    cout << "Press 1 to show all the data in the artists table\n";
    //cout << "Press 2 to insert data into the inventory table\n";
    cout << "Press 0 to close program\n";
    cin >> input;

    stmt = con->createStatement();

    while (input != '0'){
        if (input == '1') {
        string selectDataSQL = "SELECT name FROM artists";

        sql::ResultSet* res
            = stmt->executeQuery(selectDataSQL);

        // Loop through the result set and display data
        int count = 0;
        while (res->next()) {
            cout << " Artist Name " << ++count << ": "
                << res->getString("name") << endl;
        }
        //stmt = con->createStatement();
        //stmt->execute("DROP TABLE IF EXISTS inventory");
        //cout << "Finished dropping table (if existed)" << endl;
        //stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
        //cout << "Finished creating table" << endl;
        //delete stmt;
        //
        //pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
        //pstmt->setString(1, "mango");
        //pstmt->setInt(2, 150);
        //pstmt->execute();
        //cout << "One row inserted." << endl;
        //
        //pstmt->setString(1, "banana");
        //pstmt->setInt(2, 154);
        //pstmt->execute();
        //cout << "One row inserted." << endl;
        //
        //pstmt->setString(1, "dragonfruit");
        //pstmt->setInt(2, 100);
        //pstmt->execute();
        //cout << "One row inserted." << endl;
        //

        delete res;
        } if (input == '2') {
            //pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
            //string nameInput;
            //int itemQuantity;
            //cout << "\n\nInput name of item that you want to insert: ";
            //cin >> nameInput;
            //cout << "Input quantity of item: ";
            //cin >> itemQuantity;
            //pstmt->setString(1, nameInput);
            //pstmt->setInt(2, itemQuantity);
            //pstmt->execute();
            //cout << "One row inserted." << endl;
            //delete pstmt;
        }

        //cout << "\n\nPress 1 to show all the data in the inventory table\n";
        //cout << "Press 2 to insert data into the inventory table\n";
        //cout << "Press 0 to close program\n";
        cin >> input;
    }

    cout << "\n\nApplication closed. Thank you!\n";
    delete stmt;
    delete con;
    system("pause");
    return 0;
}
