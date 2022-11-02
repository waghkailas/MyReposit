#include<iostream>
#include<string.h>
#include<conio.h>
#include<vector>
#include "main.h"
#include "Test.h"

using namespace std;

int main()
{
    int exit, option, tableOption;
    string sourceTable;
    Main m;
    DataBaseConnection dbCon;
    MysqlToMssql MydbCon;
    Validation val;
    string uid, passward;
    Test testobj;

    //try
 /*   {
       dbCon.connectDB(uid ,passsward);
    }
    catch (exception e)
    {
        std::cout << "Failed to connect to the server, Try again later!";
    }*/


    while (true)
    {
        option = m.Options();
        if (option == 1)
        {
            cout << "Enter the UID\n";
            cin >> uid;
            cout << "enter passward\n";
            cin >> passward;
            try
            {
                dbCon.connectDB(uid,passward);
            }
            catch (exception e)
            {
                std::cout << "Failed to connect to the server, Try again later!";
            }

        }
        else if (option == 2)
        {
            std::cout << "\nSelect Table You Want to Replicate!:";
            ::tableName = val.TableList();
            dbCon.replicate(::tableName);
        }

        else if (option == 3)
        {
            ::tableName = val.TableList();
            while (true)
            {
                m.odbcMenu();
                exit = m.odbcChoiceMenu();
                if (exit == 1)
                {
                    break;
                }
                (void)getchar();
            }
        }
        else if (option == 4)
        {
            while (true)
            {
                m.FileMenu();
                exit = m.FileChoiceMenu();
                if (exit == 1)
                {
                    break;
                }
                (void)getchar();
            }
        }
        else if (option == 5)
        {
            
                MydbCon.ConnectToMysql();
                cout << "\n***Successfully Connected To Mysql Database***" << endl;
                std::cout << "\nSelect Table Which You Want to Replicate from Mysql to MSSQL:";
                ::MytableName = val.MysqlTableList();
                MydbCon.MysqlReplicate(::MytableName);
          
        }
        else if (option == 6)
        {
            testobj.executeUnitTestCases();
        }
        else if (option == 7)
        {
            std::cout << "Exiting Program\n";
            try
            {
                dbCon.disconnectDB();
            }
            catch (exception e)
            {
                std::cout << "Failed to disconnect the server, but closing anyway!";
            }
            break;
        }
        else if (option == 0)
        {

        }
        else
        {
            std::cout << "Invalid Option, Try Again!\n";
        }
    }

    std::cout << "//Exit//\n";
    return 0;
}


































