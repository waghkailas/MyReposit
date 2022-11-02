#pragma once
#include <iostream>
#include <sql.h>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <vector>
#include "DataBaseConnection.h"
#include "MysqlToMssql.h"
using namespace std;

class Validation : public DataBaseConnection
{
    int returnValue = 0;
    MysqlToMssql Mydbcon;

public:
    int CheckConnection()
    {
        
        SQLRETURN retCode = 0;
        SQLINTEGER autocommit;



        switch (SQLGetConnectAttr(SQLConnectionHandle, SQL_ATTR_CONNECTION_DEAD, &autocommit, 0, NULL))
        {
        case SQL_SUCCESS:
            break;
        case SQL_SUCCESS_WITH_INFO:
            break;
        case SQL_NO_DATA_FOUND:
            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
            retCode = -1;
            break;
        case SQL_INVALID_HANDLE:
            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
            retCode = -1;
            break;                  // SQL_ERROR, or SQL_INVALID_HANDLE.
        case SQL_ERROR:
            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
            retCode = -1;
            break;
        default:
            break;
        }

        if (retCode == -1)
        {
            return 0;//cout << "No\n";
        }
        else
        {
            return 1;//cout << "Yes\n";
        }
    }

    bool TableCheck(string Name)
    {
        string SQLQuery;
         SQLQuery = "SELECT TABLE_NAME FROM  Record.INFORMATION_SCHEMA.TABLES";
        flag = true;
        char* Query = &SQLQuery[0];
        exeQuery(Query);

        for (const auto& item : table)
        {
            if (Name == item)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    bool tableData(string tableName, string dataBase = "Record")
    {
        returnValue = CheckConnection();

        if (returnValue == 1)
        {

            string infoSchema = ".INFORMATION_SCHEMA.COLUMNS";
            infoSchema = dataBase + infoSchema;
            string SQLQuery = "SELECT COLUMN_NAME, DATA_TYPE FROM " + infoSchema + " WHERE TABLE_NAME = '" + tableName + "';";
            char* Query = &SQLQuery[0];
            exeQuery(Query, false, 1);
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
            cout << "Application Not Connected To Database\n";
            return false;
        }
    }

    string TableList()
    {
        returnValue = CheckConnection();
        if (returnValue == 1)
        {


            int ret = 0;
            int count = 1;
            string SourceTable;

            cout << "\nAvailable Tables:\n";
            string SQLQuery = "SELECT TABLE_NAME FROM  Record.INFORMATION_SCHEMA.TABLES";
            flag = true;
            char* Query = &SQLQuery[0];
            exeQuery(Query, false, 2);

            for (auto i = table.begin(); i != table.end(); ++i)
            {
                cout << count << ". " << *i << endl;
                count += 1;
            }

            long choice = 0;
            cout << "Select table: ";
            try
            {
                if (!(cin >> choice))
                    throw - 1;

                if (choice <= table.size() && choice > 0)
                {
                    int index = choice - 1;
                    cout << "-------------------" << endl;
                    cout << "Table Selected: " << table.at(index) << endl;
                    SourceTable = table.at(index);
                    tableData(SourceTable);
                    cout << "-------------------" << endl;
                    return SourceTable;
                }
                else
                {
                    cout << "Invalid Input\n";
                    return TableList();
                }
            }
            catch (...)
            {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid Input, Try Again!\n";
                return TableList();
            }
        }
        else
        {
            cout << "Application is Not Connected with Database\n";

        }
    
    }


    string MysqlTableList()
    {
        int ret = 0;
        int count = 1;
        string SourceTable;

        cout << "\nAvailable Tables:\n";
        string SQLQuery = "show tables in record;";
        Myflag = true;
        char* Query = &SQLQuery[0];
        Mydbcon.MyexeQuery(Query, false, 2);

        for (auto i = Mytable.begin(); i != Mytable.end(); ++i)
        {
            cout << count << ". " << *i << endl;
            count += 1;
        }

        long choice = 0;
        cout << "Select table: ";
        try
        {
            if (!(cin >> choice))
                throw - 1;

            if (choice <= Mytable.size() && choice > 0)
            {
                int index = choice - 1;
                cout << "-------------------" << endl;
                cout << "Table Selected: " << Mytable.at(index) << endl;
                SourceTable = Mytable.at(index);
                //OtableData(SourceTable);
                cout << "-------------------" << endl;
                return SourceTable;
            }
            else
            {
                cout << "Invalid Input\n";
                return MysqlTableList();
            }
        }
        catch (...)
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid Input, Try Again!\n";
            return MysqlTableList();
        }
    }


    bool checkInt(string s) 
    {
        bool checkFlag = true;
        for (int i = 0; i < s.length(); i++)
        {
            if ((int)s[i] < 48 || (int)s[i] > 57)
            {
                checkFlag = false;
                break;
            }
        }
        return checkFlag;
    }

    bool checkString(string s)
    {
        bool checkFlag = true;
        for (int i = 0; i < s.length(); i++)
        {
            if (isalpha(s[i]))
            {
                continue;
            }
            else
            {
                checkFlag = false;
                break;
            }
           /* if (65<=s[i]<=90)
            {
                checkFlag = true;
                
            }
            else if (97 <= s[i] <= 122)
            {
                checkFlag = true;
            }
            else
            {
                checkFlag = false;
                break;
            }*/
        }
        return checkFlag;

    }
    
};

















