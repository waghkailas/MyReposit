#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include "Utility.h"
#include<ctype.h>
using namespace std;

class DMLOperations : public DataBaseConnection
{
private:
    int mId, mPin;
    string mName, mPhoneNo, mSourceFile;
    int returnValue;
    Validation Vobj;

    // Methods In The Class
public:

    DMLOperations()
    {
        mId = 0;
        mName = "\0";
        mPhoneNo = "\0";
        mPin = 0;
        mSourceFile = "UserDetails.csv";
        returnValue = 0;
    }

    bool InsertRecord( int insertId, string insertName, string insertPhone, int insertPin, int rep = 0,bool testinsert=false)
    {
       // int insertId, insertPin;
       // string insertName, insertPhone;
        bool pass = true;

        returnValue = Vobj.CheckConnection();
        if (returnValue == 1)
        {

            if (testinsert == false)
            {



                cout << "Enter ID:\n";
                cin >> insertId;
                cout << "Enter Name:\n";
                cin >> insertName;
                cout << "Enter Phone Number:\n";
                cin >> insertPhone;
                cout << "Enter Pin Code:\n";
                cin >> insertPin;


                while (1)
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(256, '\n');
                        cout << "Wrong Input\n" << endl;
                        pass = false;
                    }
                    if (!cin.fail())
                    {
                        break;
                    }
                }
            }
            else
            {


                if (isdigit(insertId)==0)
                {
                    return false;
                }
                else
                {
                    return true;
                }
                if (isdigit(insertPin)==0)
                {
                    return false;
                }

                else
                {
                    return true;
                }

            }
            if (pass == true)
            {
                string SQLQuery = "INSERT INTO Record.dbo." + ::tableName + " (id, name, phone, pin) VALUES(" + to_string(insertId) + ", '" + insertName + "', '" + insertPhone + "', " + to_string(insertPin) + "); ";
                char* Query = &SQLQuery[0];
                exeQuery(Query);
                return true;
            }


            if (rep == 1)
            {
                string SQLQuery = "INSERT INTO Destination.dbo.Destination_Table (id, name, phone, pin) VALUES (" + to_string(insertId) + ",'" + insertName + "','" + insertPhone + "'," + to_string(insertPin) + ");";
                char* Query = &SQLQuery[0];
                exeQuery(Query, true);
            }
        }
        else
        {
            cout << "Application Not Connected To Database\n";
            return false;
        }
    }

    bool UpdateRecord(int updateId, int rep = 0)
    {
        int  updatePin;
        string updateName, updatePhone;

        returnValue = Vobj.CheckConnection();
        if (returnValue == 1)
        {

           // cout << "Enter id of the column you want to update\n";
           //cin >> updateId;
            cout << "Enter updated Name:\n";
            cin >> updateName;
            cout << "Enter updated Phone Number:\n";
            cin >> updatePhone;
            cout << "Enter updated Pin Code:\n";
            cin >> updatePin;


            string SQLQuery = "UPDATE Record.dbo." + ::tableName + " SET name = '" + updateName + "', phone = '" + updatePhone + "', pin = " + to_string(updatePin) + "WHERE id = " + to_string(updateId) + "; ";
            char* Query = &SQLQuery[0];
            exeQuery(Query);
            if (checkexequery == false)
            {
                return false;
            }
            else
            {
                return true;
            }
            if (rep == 1)
            {
                string SQLQuery = "UPDATE Destination.dbo.Destination_Table SET name = '" + updateName + "', phone = '" + updatePhone + "', pin = " + to_string(updatePin) + "WHERE id = " + to_string(updateId) + "; ";
                char* Query = &SQLQuery[0];
                exeQuery(Query, true);
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
        else
        {
            cout << "Application is Not Connected with Database\n";
            return false;
        }
    }

   bool DeleteRecord(int deleteId,int rep = 0)
    {
       // int deleteId;

        returnValue = Vobj.CheckConnection();
        if (returnValue == 1)
        {

            // cout << "Enter ID to be deleted\n";
            // cin >> deleteId;
            string str21 = to_string(deleteId);



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

                    string SQLQuery = "DELETE FROM Record.dbo." + ::tableName + " WHERE ID =" + to_string(deleteId) + "; ";
                    char* Query = &SQLQuery[0];
                    exeQuery(Query);
                    

                    if (rep == 1)
                    {
                        string SQLQuery = "DELETE FROM Destination.dbo.Destination_Table WHERE ID =" + to_string(deleteId) + "; ";
                        char* Query = &SQLQuery[0];
                        exeQuery(Query, 1);

                    }
                    return true;
                }
            }
        }

        else
        {
            cout << "Application is Not Connected with Database\n";
            return false;
        }


    }

    void InsertFileRecord()
    {
        cout << "Enter File Name:\n";
        cin >> mSourceFile;
        mSourceFile = mSourceFile + ".csv";

        ifstream ifile;
        ifile.open(mSourceFile);
        if (ifile)
        {
            fstream file(mSourceFile, ios::app);
            cout << "Enter the ID\n";
            cin >> mId;
            cout << "Enter the Name\n";
            cin >> mName;

            cout << "Enter the PhoneNo\n";
            cin >> mPhoneNo;

            cout << "Enter the Pin\n";
            cin >> mPin;

            file << mId << "," << mName << "," << mPhoneNo << "," << mPin << endl;
            cout << "Values were added\n";
        }
        else
        {
            cout << "Table Doesnot Exists, Try different one\n";
        }

    }

    void UpdateFileRecord()
    {
        char c;
        vector <string> lines;
        string line;
        cout << "Enter File Name:\n";
        cin >> mSourceFile;
        mSourceFile = mSourceFile + ".csv";
        cout << "Do you want to update the first record? (y/n)\n";
        cin >> c;

        if (c == 'y' || c == 'Y')
        {
            ifstream ifile;
            ifile.open(mSourceFile);
            if (ifile)
            {
                fstream file(mSourceFile, ios::in);

                while (getline(file, line))
                    lines.push_back(line);

                file.close();

                cout << "Enter new ID:\n";
                cin >> mId;
                cout << "Enter new Name:\n";
                cin >> mName;
                cout << "Enter new Phone Number:\n";
                cin >> mPhoneNo;
                cout << "Enter new Pin Code:\n";
                cin >> mPin;

                fstream file1(mSourceFile, ios::out);

                for (int i = 0; i < lines.size(); i++)
                {
                    if (i == 0)
                    {
                        file1 << mId << "," << mName << "," << mPhoneNo << "," << mPin << endl;
                    }
                    else
                        file1 << lines[i] << endl;
                }

                file1.close();
                cout << "Record Updated Successfully\n";
            }
            else
            {
                cout << "Table doesnot exists, Try different name\n";
            }
        }
        else if (c == 'n' || c == 'N')
            cout << "No changes made\n";
        else
            cout << "Invalid input\n";
    }

    void DeleteFileRecord()
    {
        char c;
        string line;
        vector <string> lines;
        cout << "Enter File Name:\n";
        cin >> mSourceFile;
        mSourceFile = mSourceFile + ".csv";
        cout << "Do you want to delete the first record? (y/n)\n";
        cin >> c;

        if (c == 'y' || c == 'Y')
        {

            ifstream ifile;
            ifile.open(mSourceFile);
            if (ifile)
            {
                fstream file(mSourceFile, ios::in);

                while (getline(file, line))
                    lines.push_back(line);

                file.close();

                fstream file1(mSourceFile, ios::out);

                for (int i = 0; i < lines.size(); i++)
                {
                    if (i == 0)
                        continue;

                    file1 << lines[i] << endl;
                }

                file1.close();
                cout << "Record Deleted Successfully\n";
            }
            else
            {
                cout << "Table Doesnot exists, Try different name\n";
            }
        }
        else if (c == 'n' || c == 'N')
        {
            cout << "Nothing Deleted\n";
        }
        else
            cout << "Invalid Details\n";
    }

    ~DMLOperations()
    {

    }

};























