#pragma once
#include<iostream>
#include<string.h>
#include<vector>
#include<fstream>
#include "Utility.h"
#include "DataBaseConnection.h"
using namespace std;

class CAndT:public DataBaseConnection
{
    string mtableName;
    Validation Vobj;
    int returnValue;

public:

    CAndT()
    {
        returnValue = 0;

    }

    bool CreateTable(string mtableName="Demo")
    {

        returnValue = Vobj.CheckConnection();
        if (returnValue == 1)
        {
            if (utest == false)
            {


                cout << "Enter name of new table\n";
                cin >> mtableName;
            }

            
            checkexequery = true;

            mtableName = "Record.dbo." + mtableName;
            string SQLQuery = "CREATE TABLE " + mtableName + "(id int NOT NULL, name varchar(50), phone varchar(10), pin int, PRIMARY KEY (ID))";
            char* Query = &SQLQuery[0];
            exeQuery(Query);

            if (checkexequery == true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << "Application is Not Connected with Database\n";
            return false;
        }
    }

   bool TruncateTable(string TableName)
    {
       char choice;

        returnValue = Vobj.CheckConnection();
        if (returnValue == 1)
        {

            if (utest == false)
            {



               
                cout << "Are you sure you want to truncate '" << TableName << "' ?(y/n): ";
                cin >> choice;
            }
            else
            {
                choice = 'y';
            }
            TableName = "Record.dbo." + TableName;
            if (choice == 'y' || choice == 'Y')
            {
                string SQLQuery = "TRUNCATE TABLE " + TableName + "; ";
                char* Query = &SQLQuery[0];
                exeQuery(Query);
                if (checkexequery == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                cout << "No changes made\n";
            }
        }
        else
        {
            cout << "Application is Not connected to Database\n";
            return false;
        }
    }

    void CreateAFile()
    {
        cout << "Enter the name of the table which you want to make : \n";
        cin >> mtableName;
        mtableName = mtableName + ".csv";

        ifstream ifile;
        ifile.open(mtableName);
        if (ifile)
        {
            cout << "File Already Exists, Try Different Name\n";
        }
        else
        {
            ofstream file(mtableName, ios::out);
            cout << "New table created\n";
        }

    }

    void TruncateAFile()
    {

        

            char c;
            string line;
            vector <string> lines;

            cout << "Enter the name of the table\n";
            cin >> mtableName;
            mtableName = mtableName + ".csv";
            cout << "Do you want to truncate the table? (y/n)\n";
            cin >> c;

            if (c == 'y' || c == 'Y')
            {
                ifstream ifile;
                ifile.open(mtableName);
                if (ifile) {
                    fstream file1(mtableName, ios::out);
                    file1.close();
                    cout << "Table Truncated Successfully\n";
                }
                else {
                    cout << "file doesn't exist\n";
                }
            }
            else if (c == 'n' || c == 'N')
            {
                cout << "No changes made\n";
            }
            else
                cout << "Invalid Details\n";
       
    }

    ~CAndT()
    {

    }
};













