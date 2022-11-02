#pragma once
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <string.h>
#include <vector>

using namespace std;

#define BUFFERSIZE  1024
#define MAX_TABLES 100
SQLHANDLE SQLEnvHandle;
SQLHANDLE SQLConnectionHandle;
SQLHANDLE SQLStatementHandle;
SQLRETURN retCode;
BOOL error;
bool flag = false;
vector <string> column;
vector <string> table;
string tableName;
bool checkexequery = true;
bool utest = false;

class DataBaseConnection
{
public:

    SQLCHAR SQLState[1024];
    SQLCHAR message[1024];
    SQLRETURN retstate;
    SQLCHAR retConString[1024];
    int tableOption;

    DataBaseConnection()
    {
        SQLEnvHandle = NULL;
        SQLConnectionHandle = NULL;
        SQLStatementHandle = NULL;
        retCode = 0;
        retstate = 0;
    }
    void showSQLError(unsigned int handleType, const SQLHANDLE& handle)
    {
        if (utest == false)
        {


            if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
            {
                cout << "Exception Occurred:\n\n";
                cout /*<< "SQL driver message: "*/ << message << "." << endl;
            }
        }
        // Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information     
        error = true;
    }
    bool connectDB(string id,string passward)
    {
        retCode = 0;

        retstate = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle);
        if (SQL_SUCCESS != retstate)
        {
            return false;
        }

        retstate = SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
        if (SQL_SUCCESS != retstate)
        {
            return false;
        }

        retstate = SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle);
        if (SQL_SUCCESS != retstate)
        {
            return false;
        }

        SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
        if (SQL_SUCCESS != retstate)
        {
            return false;
        }


        string driverConnect = "DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=master; UID=" + id + "; PWD=" + passward + "; ";
        char* chardriverConnect = &driverConnect[0];
        switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)chardriverConnect, SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT))
        {

        case SQL_SUCCESS:
            return true;
            break;
        case SQL_SUCCESS_WITH_INFO:
            return true;
            break;
        case SQL_NO_DATA_FOUND:
            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
            retCode = -1;
            break;
        case SQL_INVALID_HANDLE:
            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
            retCode = -1;
            break;
        case SQL_ERROR:
            showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
            retCode = -1;
            break;
        default:
            break;
        }
        if (retCode == -1)
        {
            return false;
        }
        else
        {
            return true;
        }

    }
    void exeQuery(const char SQLQuery[] = "SELECT * FROM Record.dbo.UserDetails", boolean rep = false, int func = -1)
    {
        if (retCode == -1)
        {
            checkexequery = false;

            return;
        }

        retstate = SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle);
        if (SQL_SUCCESS != retstate)
        {
            checkexequery = false;
            return;
        }

        if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
        {
            checkexequery = false;
            showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
            //checkexequery = false;
        }
        else {
            if (func == 1)
            {
                checkexequery = true;
                error = false;
                column.clear();
                char columnName[40], dataType[40];
                cout << "Table Structure:\n";
                while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
                {
                    SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &columnName, sizeof(columnName), NULL);
                    SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &dataType, sizeof(dataType), NULL);
                    cout << columnName << " " << dataType << endl;
                    column.push_back(columnName);
                    column.push_back(dataType);
                }
                (void)getchar();
            }
            else if (func == 2)
            {
                checkexequery = true;
                error = false;
                table.clear();
                char tablesNameVar[256] = { '\0' };
                while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
                {
                    // Fetches the next rowset of data from the result
                    SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &tablesNameVar, sizeof(tablesNameVar), NULL);
                    table.push_back(tablesNameVar);
                }
            }
            else
            {
                checkexequery = true;
                error = false;
                char name[256], phone[10];
                int pin, id;
                if (func == 0)
                {
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "||\tID\t\tName\t\tPhone\t\t\tPin\t||\n";
                    cout << "--------------------------------------------------------------------------\n";

                    while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
                    {
                        // Fetches the next rowset of data from the result
                        cout << "||\t";
                        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &id, sizeof(id), NULL);
                        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &name, sizeof(name), NULL);
                        SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &phone, sizeof(phone), NULL);
                        SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &pin, sizeof(pin), NULL);
                        // Retrieves data for a single column in the result set
                        cout << id << "\t\t" << name << "\t\t" << phone << "\t\t" << pin << "\t||" << endl;
                    }
                    cout << "--------------------------------------------------------------------------\n";
                }
            }
        }
        /*if (error == false)
        {
            if (rep == false && func != 1 && func != 2)
                cout << "---Query Performed Successfully---\n";
        }
        else
        {
            cout << "Query couldn't be performed properly\n";
        }*/
    }
    void disconnectDB()
    {
        SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
        SQLDisconnect(SQLConnectionHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
    }
    bool replicate(string SourceTable, string sourceDatabase = "Record", string destinationDatabase = "Destination")
    {
        checkexequery = true;
        string SQLQuery = "DROP TABLE IF EXISTS " + destinationDatabase + ".dbo." + SourceTable + ";";
        char* SQLTruncate = &SQLQuery[0];
        exeQuery(SQLTruncate, true);
        
        SQLQuery = "SELECT * INTO " + destinationDatabase + ".dbo." + SourceTable + " FROM " + sourceDatabase + ".dbo." + SourceTable + " ;";
        char* Query = &SQLQuery[0];
        exeQuery(Query, true);
        if (utest == true)
        {


            if (checkexequery == false)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        if (error == false)
        {
            cout << "Replicated Table Details:\n";
            SQLQuery = "SELECT * FROM " + destinationDatabase + ".dbo." + SourceTable + " ;";
            char* Query = &SQLQuery[0];
            exeQuery(Query, false, 0);
            if (utest == true)
            {


                if (checkexequery == false)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
    }
    int showTables()
    {
        cout << "\nAvailable Source Tables:\n";
        string SQLQuery = "SELECT TABLE_NAME FROM Record.INFORMATION_SCHEMA.TABLES";
        char* Query = &SQLQuery[0];
        exeQuery(Query, false, 2);
        cin >> tableOption;
        return tableOption;
    }
};
























