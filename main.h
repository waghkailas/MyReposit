#pragma once
#include<iostream>
#include<string.h>
#include "DataBaseConnection.h"
#include "DMLOperations.h"
#include "DQLOperations.h"
#include "CreateAndTruncate.h"
#include "Utility.h"
#include "MysqlToMssql.h"
using namespace std;

class Main : public DMLOperations, public DQLOperations, public CAndT,public MysqlToMssql
{
private:
    int mChoice, mOption;
public:
    int Options()
    {
        cout << "\n--------Options---------\n";
       
        cout << "1.connect to DataBase\n";
        cout << "2. Replicate Options\n";
        cout << "3. ODBC Options\n";
        cout << "4. File Handling Options\n";
        cout << "5. Replicate Mysql TO MSSQL\n";
        cout << "6.Unit Testing\n";
        
        cout << "7. Exit\n";
        cout << "-------------------------\n";
        cout << "Enter your choice:\t";
        try
        {
            if (cin >> mOption)
            {
                if (mOption == 1)
                {
                    return 1;
                }
                else if (mOption == 2)
                {
                    return 2;
                }
                else if (mOption == 3)
                {
                    return 3;
                }
                else if (mOption == 4)
                {
                    return 4;
                }
                else if (mOption == 5)
                {
                    return 5;
                }
                else if (mOption == 6)
                {
                    return 6;
                }
                else if (mOption == 7)
                {
                    return 7;
                }
                else
                {
                    return -1;
                }
            }
            else
                throw - 1;

        }
        catch (...)
        {
            cout << "Exception Occurred, Invalid Input\nProviding Options again!\n";
            cin.clear();
            cin.ignore(256, '\n');
            return 0;
        }
    }
    void odbcMenu()
    {
       // int deleteId = 0;

        cout << "\n----------MENU----------\n";
        cout << "1. Create a Table\n";
        cout << "2. Truncate a Table\n";
        cout << "3. Insert a Record\n";
        cout << "4. Update a Record\n";
        cout << "5. Delete a Record\n";
        cout << "6. Search a Record\n";
        cout << "7. Print Records\n";
        cout << "8. Clear Screen\n";
        cout << "9. Return to previous menu\n";
        cout << "10.Mysql to Mssql\n";
        cout << "------------------------\n";
        cout << "Enter your choice:\t";

        try
        {
            if (!(cin >> mChoice))
            {
                throw - 1;
            }
        }
        catch (...)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Exception Occurred, Invalid Input\nProviding Options again!\n";
            odbcMenu();
        }

    }
    int odbcChoiceMenu()
    {
        int deleteId = 0;
        bool returnvalue = false;
        switch (mChoice)
        {
        case 1: CreateTable();
            return 0;
            break;
        case 2: TruncateTable(::tableName);
            return 0;
            break;
        case 3: InsertRecord(5,"Raj","9878994543",414501);
            return 0;
            break;
        case 4:
            cout << "Enter id to Update\n";
            cin >> deleteId;

           returnvalue= UpdateRecord(deleteId);
           if (returnvalue = true)
           {
               cout << "success\n";
           }
           else
           {
               cout << "failed\n";
           }
            return 0;
            break;
        case 5: 
           // int deleteId = 0;
            cout << "Enter ID to be deleted\n";
            cin >> deleteId;
             returnvalue =DeleteRecord(deleteId);
            if (returnvalue == true)
            {
                cout << "success\n";
            }
            else
            {
                cout << "failed\n";
            }
            
            //return 0;
            break;
        case 6: SearchRecords();
            return 0;
            break;
        case 7: ShowRecord();
            return 0;
            break;
        case 8: system("CLS");
            return 0;
            break;
        case 9: return 1;

            break;
        case 10: ConnectToMysql();
            return 0;
            break;
        default: cout << "Invalid Choice, Try Again!\n";
            return 0;
            break;
        }
    }
    void FileMenu()
    {
        cout << "\n----------MENU----------\n";
        cout << "1. Create a new file\n";
        cout << "2. Insert a new Record\n";
        cout << "3. Update first record\n";
        cout << "4. Delete first Record\n";
        cout << "5. Show all Records\n";
        cout << "6. Truncate a file\n";
        cout << "7. Clear Screen\n";
        cout << "8. Return to previous menu\n";
        cout << "------------------------\n";
        cout << "Enter your choice:\t";
        cin >> mChoice;
        try
        {
            if (!(cin >> mChoice))
            {
                throw - 1;
            }
        }
        catch (...)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Exception Occurred, Invalid Input\nProviding Options again!\n";
            FileMenu();
        }
    }
    int FileChoiceMenu()
    {
        switch (mChoice)
        {
        case 1: CreateAFile();
            return 0;
            break;
        case 2: InsertFileRecord();
            return 0;
            break;;
        case 3: UpdateFileRecord();
            return 0;
            break;
        case 4: DeleteFileRecord();
            return 0;
            break;
        case 5: ShowFileRecord();
            return 0;
            break;
        case 6: TruncateAFile();
            return 0;
            break;
        case 7: system("CLS");
            return 0;
            break;
        case 8: return 1;
            break;
        default: cout << "Invalid Choice\n";
            return 0;
            break;
        }
    }
    void replicateMenu()
    {
        cout << "\n----------MENU----------\n";
        cout << "1. Insert new Record\n";
        cout << "2. Update a Record\n";
        cout << "3. Delete a Record\n";
        cout << "4. Show all records of Destination Table\n";
        cout << "5. Clear screen\n";
        cout << "6. Exit\n";
        cout << "---------------------------\n";
        cout << "Enter your choice\t";
        cin >> mChoice;
    }
    int replicateChoiceMenu()
    {
        switch (mChoice)
        {
        case 1: InsertRecord(6,"akash","7767546534",456794,true,false);
            return 0;
            break;
        case 2: UpdateRecord(true);
            return 0;
            break;
        case 3: DeleteRecord(true);
            return 0;
            break;
        case 4: ShowRecord(true);
            return 0;
            break;
        case 5: system("CLS");
            return 0;
            break;
        case 6: return 1;
            break;
        default: cout << "Invalid Choice\n";
            return 0;
            break;
        }
    }
};



























