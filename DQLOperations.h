#pragma once
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<fstream>
#include <ctype.h>
#include "Utility.h"
#include "DataBaseConnection.h"

using namespace std;

class DQLOperations : public DataBaseConnection
{
private:
	int mId;
	int mchoice;
	string mline, mword;
	DataBaseConnection dbcon;
	Validation Vobj;
	int 	returnValue;

public:
	DQLOperations()
	{
		mId = 0;
		mchoice = 0;
		returnValue = 0;
	}
	bool ShowRecord(int rep = 0,string NewTableName=::tableName)
	{
		checkexequery = true;
		returnValue = Vobj.CheckConnection();
		if (returnValue == 1)
		{


			if (rep == 0)
			{
				//cout << "\nThe values are:\n";
				string SQLQuery = "SELECT * FROM Record.dbo." + NewTableName + ";";
				char* Query = &SQLQuery[0];
				exeQuery(Query, false, 0);
				if (checkexequery == false)
				{
					return false;
				}
				else
				{
					return true;
				}
				(void)getchar();
			}
			else
			{
				char SQLQuery[] = "SELECT * FROM Destination.dbo.Destination_Table";
				cout << "\nThe Replicate Table values are:\n";
				exeQuery(SQLQuery, 1);
				(void)getchar();
			}
		}
		else
		{
			cout << "Application is Not Connected To Database\n";
		}
	}

	void SearchRecords()
	{
		int inputvalue;
		bool returnvalue;
		string inputName;
		returnValue =Vobj.CheckConnection();
		if (returnValue == 1)
		{

			cout << "1:Search by ID\n";
			cout << "2:Search by Name\n";
			cout << "3:Search by Phone Number\n";
			cout << "4:Search by PIN\n";

			cout << "Enter the choice\n";
			cin >> mchoice;

			switch (mchoice)
			{
			case 1: 
				cout << "Enter the Id to serch\n";
				cin >> inputvalue;
				returnvalue=SearchByID(inputvalue);
				if (returnvalue == true)
				{
					cout << "success\n";
				}
				else
				{
					cout << "failed\n";
				}
				break;
			case 2:
				cout << "Enter the Name to serch\n";
				cin >> inputName;
				returnvalue=SearchByName(inputName);
				if (returnvalue == true)
				{
					cout << "success\n";
				}
				else
				{
					cout << "failed\n";
				}
				break;
			case 3: cout << "Enter the Phoneno to serch\n";
				cin >> inputName;
				returnvalue=SearchByPhoneNo(inputName);
				if (returnvalue == true)
				{
					cout << "success\n";
				}
				else
				{
					cout << "failed\n";
				}


				break;
			case 4: cout << "Enter the PIN to search\n";
				cin >> inputvalue;
				returnvalue=SearchByPIN(inputvalue);
				if (returnvalue == true)
				{
					cout << "success\n";
				}
				else
				{
					cout << "failed\n";
				}
				
				break;
			default: cout << "Invalid Choice\n";
			}
		}
		else
		{
			cout << "Application is Not Connected To Database\n";
		}
	}

	bool SearchByID(int searchId) {
		//int searchId;
		//cout << "Enter ID to be searched\n";
		//cin >> searchId;
		string str21 = to_string(searchId);

		

		if (Vobj.checkInt(str21)==false)
		{
			return false;
		}
		else
		{
			if (utest == true)
			{
				return true;
			}
			else
			{


				string SQLQuery = "SELECT * FROM Record.dbo." + ::tableName + " WHERE id = " + to_string(searchId) + ";";
				char* Query = &SQLQuery[0];
				exeQuery(Query, false, 0);
				return true;
			}
		}

	}

	bool SearchByName(string searchName)
	{
		//string searchName;

		//cout << "Enter Name to be searched\n";
        // cin >> searchName;
		if (Vobj.checkString(searchName) == true)
		{



			string SQLQuery = "SELECT * FROM Record.dbo." + ::tableName + " WHERE name ='" + searchName + "';";
			char* Query = &SQLQuery[0];
			exeQuery(Query, false, 0);
			return true;
		}
		else
		{
			return false;
		}

	}

	bool SearchByPhoneNo(string searchPhone)
	{
		//string searchPhone;

		//cout << "Enter Phone Number to be searched\n";
		//cin >> searchPhone;

		if (Vobj.checkInt(searchPhone) == true)
		{




			string SQLQuery = "SELECT * FROM Record.dbo." + ::tableName + " WHERE phone = '" + searchPhone + "';";
			char* Query = &SQLQuery[0];
			exeQuery(Query, false, 0);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool SearchByPIN(int searchPin) {
		//int searchPin;
		//cout << "Enter Pin Number to be searched\n";
		//cin >> searchPin;
		string str21 = to_string(searchPin);

		if (Vobj.checkInt(str21) == false)
		{
			return false;
		}
		else
		{
			if (utest == true)
			{
				return true;
			}
			else
			{

				string SQLQuery = "SELECT * FROM Record.dbo." + ::tableName + " WHERE pin = " + to_string(searchPin) + ";";
				char* Query = &SQLQuery[0];
				exeQuery(Query, false, 0);
				return true;
			}
		}
	}

	void ShowFileRecord()
	{
		string mSourceFile;
		cout << "Enter File Name:\n";
		cin >> mSourceFile;
		mSourceFile = mSourceFile + ".csv";

		ifstream ifile;
		ifile.open(mSourceFile);
		if (ifile)
		{
			fstream file;
			file.open(mSourceFile);

			while (file.good())
			{
				getline(file, mword, ',');
				cout << mword << " ";
			}
		}
		else
		{
			cout << "Table doesnot exists, try different name\n";
		}

		(void)getchar();
	}

	~DQLOperations()
	{

	}

};


















