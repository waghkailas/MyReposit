#pragma once
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <string.h>
#include <vector>
#include <iterator>
#include <map>
#include "DataBaseConnection.h"
//#include "Utility.h"

using namespace std;

#define BUFFERSIZE  1024
#define MAX_TABLES 100
SQLHANDLE MySQLEnvHandle;
SQLHANDLE MySQLConnectionHandle;
SQLHANDLE MySQLStatementHandle;
SQLRETURN MyretCode;
BOOL Myerror;
bool Myflag = false;
map<string, string> tableStructure;
static vector <string> Mytable;
string MytableName;



class MysqlToMssql
{
public:
    SQLCHAR SQLState[1024];
    SQLCHAR message[1024];
    SQLRETURN Myretstate;
    SQLCHAR retConString[1024];
    int tableOption;
    DataBaseConnection dbCon;
    //Validation Vobj;

    MysqlToMssql()
    {
        MySQLEnvHandle = NULL;
        MySQLConnectionHandle = NULL;
        MySQLStatementHandle = NULL;
        MyretCode = 0;
        Myretstate = 0;

    }
    void MyshowSQLError(unsigned int handleType, const SQLHANDLE& handle)
    {
        if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
        {
            cout << "Exception Occurred:\n\n";
            cout /*<< "SQL driver message: "*/ << message << "." << endl;
        }
        // Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information     
        error = true;
    }

    void ConnectToMysql()
    {
        Myretstate = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &MySQLEnvHandle);
        if (SQL_SUCCESS != Myretstate)
        {
            return;
        }

        Myretstate = SQLSetEnvAttr(MySQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
        if (SQL_SUCCESS != Myretstate)
        {
            return;
        }

        Myretstate = SQLAllocHandle(SQL_HANDLE_DBC, MySQLEnvHandle, &MySQLConnectionHandle);
        if (SQL_SUCCESS != Myretstate)
        {
            return;
        }

        SQLSetConnectAttr(MySQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
        if (SQL_SUCCESS != Myretstate)
        {
            return;
        }

        switch (SQLDriverConnect(MySQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={MySQL ODBC 8.0 ANSI Driver}; SERVER=localhost, 3306;MULTI_HOST=1; DATABASE=record; UID=root; PWD=Kailas@2000;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT))
        {
        case SQL_SUCCESS:
           // cout << "Connected";
            break;
        case SQL_SUCCESS_WITH_INFO:
            break;
        case SQL_NO_DATA_FOUND:
            MyshowSQLError(SQL_HANDLE_DBC, MySQLConnectionHandle);
            retCode = -1;
            break;
        case SQL_INVALID_HANDLE:
            MyshowSQLError(SQL_HANDLE_DBC, MySQLConnectionHandle);
            retCode = -1;
            break;
        case SQL_ERROR:
            MyshowSQLError(SQL_HANDLE_DBC, MySQLConnectionHandle);
            retCode = -1;
            break;
        default:
            break;
        }


    }

    void MyexeQuery(const char SQLQuery[] = "SELECT * FROM employee", boolean rep = false, int func = -1)
    {
        if (retCode == -1)
            return;

        Myretstate = SQLAllocHandle(SQL_HANDLE_STMT, MySQLConnectionHandle, &MySQLStatementHandle);
        if (SQL_SUCCESS != Myretstate)
        {
            return;
        }

        if (SQL_SUCCESS != SQLExecDirect(MySQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
        {
            MyshowSQLError(SQL_HANDLE_STMT, MySQLStatementHandle);
        }
        else {
            if (func == 1)
            {
                error = false;
                //column.clear();
                char columnName[40] = { 0 }, dataType[40] = { 0 };
                cout << "Table Structure:\n";
                while (SQLFetch(MySQLStatementHandle) == SQL_SUCCESS)
                {
                    SQLGetData(MySQLStatementHandle, 1, SQL_C_DEFAULT, &columnName, sizeof(columnName), NULL);
                    SQLGetData(MySQLStatementHandle, 2, SQL_C_DEFAULT, &dataType, sizeof(dataType), NULL);
                    cout << columnName << " " << dataType << endl;
                    tableStructure.insert(pair<string, string>(columnName, dataType));
                }
                cout << "========================\n";
                (void)getchar();
            }
            else if (func == 2)
            {
                error = false;
                Mytable.clear();
                char tablesNameVar[256] = { '\0' };
                while (SQLFetch(MySQLStatementHandle) == SQL_SUCCESS)
                {
                    // Fetches the next rowset of data from the result
                    SQLGetData(MySQLStatementHandle, 1, SQL_C_DEFAULT, &tablesNameVar, sizeof(tablesNameVar), NULL);
                    Mytable.push_back(tablesNameVar);
                }
            }
            else
            {
                error = false;
                char name[256], phone[10];
                int pin, id;
                if (func == 0)
                {
                    cout << "--------------------------------------------------------------------------\n";
                    cout << "||\tID\t\tName\t\tPhone\t\t\tPin\t||\n";
                    cout << "--------------------------------------------------------------------------\n";

                    while (SQLFetch(MySQLStatementHandle) == SQL_SUCCESS)
                    {
                        // Fetches the next rowset of data from the result
                        cout << "||\t";
                        SQLGetData(MySQLStatementHandle, 1, SQL_C_DEFAULT, &id, sizeof(id), NULL);
                        SQLGetData(MySQLStatementHandle, 2, SQL_C_DEFAULT, &name, sizeof(name), NULL);
                        SQLGetData(MySQLStatementHandle, 3, SQL_C_DEFAULT, &phone, sizeof(phone), NULL);
                        SQLGetData(MySQLStatementHandle, 4, SQL_C_DEFAULT, &pin, sizeof(pin), NULL);
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

    void getTableStructure(const char SQLQuery[] = "SELECT * FROM ODBC_Details.dbo.UserDetails")
    {
        if (retCode == -1)
            return;

       dbCon.retstate = SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle);
        if (SQL_SUCCESS != dbCon.retstate)
        {
            return;
        }

        if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
        {
            dbCon.showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
        }
        else {
            error = false;
            column.clear();
            char columnName[40], dataType[40];
            while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
            {
                SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &columnName, sizeof(columnName), NULL);
                SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &dataType, sizeof(dataType), NULL);
                tableStructure.insert(pair<string, string>(columnName, dataType));
            }
            (void)getchar();
        }
    }

    void  getSourceTableStructure(string SourceTable)
    {
        
            string SQLQuery = "SHOW COLUMNS FROM record. "+ SourceTable + ";";
            char* SQLTruncate = &SQLQuery[0];

            MyexeQuery(SQLTruncate, true, 1);
            //cout << "Present in get source structure\n";

        

    }

    void UpdateDataTypesForDestinationTableQuery() // Data Mapping
    {

        map<string, string>::iterator itr;
        //CREATE TABLE mysql_db.UserDetails2(ID int, Name1 varchar(100), Phone varchar(20), Pin int);
        for (itr = tableStructure.begin(); itr != tableStructure.end(); ++itr)
        {
            itr->first + " " + itr->second;

            //itr->second = "int";
            // (*itr).second = "int";
            //myMap.find("two")->second = 22;

            if ("varchar(255)" == itr->second) {

                itr->second = "varchar(100)";
            }
            if ("intchar(255)" == itr->second) {



                itr->second = "int";
            }
        }
    }

    string CreateDestinationTableQuery(string SourceTable)
    {

        string newTableQuery = "CREATE TABLE Record.dbo." + SourceTable + " (";
        map<string, string>::iterator itr;
        int i = 0;


        UpdateDataTypesForDestinationTableQuery(); // Data Mapping

        for (itr = tableStructure.begin(); itr != tableStructure.end(); ++itr)
        {
            newTableQuery = newTableQuery + itr->first + " " + itr->second;
           // cout << "\ni = " << i << endl;
            if (++i < tableStructure.size()) {
                newTableQuery = newTableQuery + ",";
            }
        }
        newTableQuery = newTableQuery + ");";
       // cout << "\n New Query : \n" + newTableQuery + "\n"; //CREATE TABLE STUDENTS(ID NUMBER, NAME VARCHAR2, PHONE VARCHAR2, PIN VARCHAR2);

        //UpdateDataTypesForDestinationTableQuery() // Data Mapping

       // cout << "\n New Query after data mapping : \n" + newTableQuery + "\n";

        //        CREATE TABLE Persons(   PersonID int,  LastName varchar,  FirstName varchar,   Address varchar,  City varchar );
        return newTableQuery;
    }


    void insertDataIntoDestinationTable(string tableName)
    {
        string sourceQuery = "SELECT ";
        int i = 0;
        for (auto itr = tableStructure.begin(); itr != tableStructure.end(); ++itr)
        {
            sourceQuery = sourceQuery + itr->first;
            if (++i < tableStructure.size()) {
                sourceQuery = sourceQuery + ",";
            }
        }
        sourceQuery = sourceQuery + " FROM record." + tableName + ";";

        //cout << sourceQuery<<"\n";

        char* SQLQuery = &sourceQuery[0];
        if (retCode == -1)
            return;

        Myretstate = SQLAllocHandle(SQL_HANDLE_STMT, MySQLConnectionHandle, &MySQLStatementHandle);
        if (SQL_SUCCESS != Myretstate)
        {
            return;
        }

        if (SQL_SUCCESS != SQLExecDirect(MySQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
        {
            MyshowSQLError(SQL_HANDLE_STMT, MySQLStatementHandle);
        }
        else
        {
            // 2 Option insert all in one shot
            // insert each record

            while (SQLFetch(MySQLStatementHandle) == SQL_SUCCESS)
            {
                string columnName, dataType;

                map<string, string>::iterator itr, itr1;

                string insertQuery = "INSERT INTO Record.dbo." + tableName + " (";

                int i = 0;
                for (itr = tableStructure.begin(); itr != tableStructure.end(); ++itr)
                {
                    insertQuery = insertQuery + itr->first;
                    if (++i < tableStructure.size()) {
                        insertQuery = insertQuery + ",";
                    }
                }
                insertQuery = insertQuery + ") VALUES (";


                i = 0;
                for (itr = tableStructure.begin(); itr != tableStructure.end(); ++itr)
                {
                    int intValue;
                    char charValue[100];
                    string dType = itr->second;
                    i++;
                    if (dType == "int")
                    {
                        SQLGetData(MySQLStatementHandle, i, SQL_C_DEFAULT, &intValue, sizeof(intValue), NULL);
                        insertQuery = insertQuery + to_string(intValue);
                    }
                    else if (dType == "varchar(100)")
                    {
                        SQLGetData(MySQLStatementHandle, i, SQL_C_DEFAULT, &charValue, sizeof(dType), NULL);
                        string value = &charValue[0];
                        insertQuery = insertQuery + "'" + value + "'";
                    }
                    else
                    {
                        SQLGetData(MySQLStatementHandle, i, SQL_C_DEFAULT, &charValue, sizeof(dType), NULL);
                        string value = &charValue[0];
                        insertQuery = insertQuery + "'" + value + "'";
                    }
                    if (i < tableStructure.size()) {
                        insertQuery = insertQuery + ",";

                    }
                    insertQuery = insertQuery + " ";

                }

                insertQuery = insertQuery + ");";

               // cout << insertQuery << "\n";
                char* mySQLQuery = &insertQuery[0];
                dbCon.exeQuery(mySQLQuery);

            }
            if (error == false)
                cout << "\nTable Replication From Mysql To MsSql Done Successful\n";
            else
                cout << "Table Couldn't be Replicated, Task Failed\n";
        }
    }


    void MysqlReplicate(string SourceTable, string sourceDatabase = "record", string destinationDatabase = "Record")
    {
       
            //connect to mssql
            tableStructure.clear();
            string SQLQuery = "DROP TABLE IF EXISTS " + destinationDatabase + ".dbo." + SourceTable + ";";   //run on mssql
            char* SQLTruncate = &SQLQuery[0];
            dbCon.exeQuery(SQLTruncate, true);   //deleting destination table from mssql if exist

            getSourceTableStructure(SourceTable);   //run on oracle this function will fill the map of column name and datatype of source table
            string newTableQuery = CreateDestinationTableQuery(SourceTable);  //creates query for creating new table in destination database

            //CREATE TABLE STUDENTS(ID NUMBER, NAME VARCHAR2, PHONE VARCHAR2, PIN VARCHAR2);
            //CREATE TABLE STUDENTS ID NUMBER, NAME VARCHAR2, PHONE VARCHAR2, PIN VARCHAR2, );
            //        CREATE TABLE Persons(   PersonID int,  LastName varchar,  FirstName varchar,   Address varchar,  City varchar );

            char* Query = &newTableQuery[0];
            dbCon.exeQuery(Query, true);         //passing query for creating new table on destination

            insertDataIntoDestinationTable(SourceTable);    //it will copy each record from source table and insert it into destination table


            if (error == false)
            {
                cout << "Replicated Table Details:\n";
                cout << "Replicate end point Destination:MsSql\n";
                cout << "Destination Database:-" << destinationDatabase << "  " << " Destination Table:-" << SourceTable << "\n";
                SQLQuery = "SELECT * FROM " + destinationDatabase + ".dbo." + SourceTable + " ;";
                char* Query = &SQLQuery[0];
                dbCon.exeQuery(Query, false, 0);
            }
       

            //return;
        }



     };




















       


























