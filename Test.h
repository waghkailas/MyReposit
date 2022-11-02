#pragma once
#include<iostream>
#include"DataBaseConnection.h"
#include"Utility.h"
#include "DMLOperations.h"
#include "DQLOperations.h"
#include "CreateAndTruncate.h"
using namespace std;
class Test 
{
public:
    DataBaseConnection dbCon;
    Validation Vobj;
    DMLOperations DMLobj;
    DQLOperations DQLobj;
    CAndT CTobj;
    bool CheckConnection()
    {
        cout << "Test cases for connect db function  \n";
        cout << "Wrong Username Password DB Connection Test : ";
        if (dbCon.connectDB("Kailas", "Kailas123") == true)
        {
            cout << "Failed\n";
        }
        else
        {
            cout << "Passed\n";
        }



        cout << "Correct Username Password DB Connection Test : ";
        if (dbCon.connectDB("myemp", "myPW") == false)
        {
            cout << "Failed\n";
        }
        else
        {
            cout << "Passed\n";
        }




        return true;



    }

    bool CheckCreateAndTruncate()
     {

    
    
    }

    bool testCheckTable()
    {
        dbCon.connectDB("myemp", "myPW");
        
        cout << "************************************************************************************************\n";
        cout << "test cases for CheckTable function check\n";
        cout << "Wrong Table Name test:\n";

        if (Vobj.TableCheck("abcdefg") == true)
        {

            cout << "Failed\n";
        }
        else
            cout << "Passed\n";
       

        cout << "Correct table name from dataBase:\n";

        if (Vobj.TableCheck("UserDetails") == false)
        {
            cout << " Failed\n";
        }
        else
        {
            cout << "Passed\n";
        }

        cout << "Wrong input with special charater check:\n";

        if (Vobj.TableCheck("@#$$%^%^%") == true)
        {
            cout << "Failed\n";
        }
        else
        {
            cout << "Passed\n";
        }


        return true;
    }

    bool checkDeleteRecord()
    {
        dbCon.connectDB("myemp", "myPW");
        cout << "**************************************************************************************\n";
        cout << "test cases for Delete function check\n";
        cout << "wrong Id  check:\n";
        if (DMLobj.DeleteRecord('@') == false)
        {
            cout << "passed\n";
        }
        else
        {
            cout << "failed\n";
        }
        cout << "Correct Delete ID Check:\n";
        if (DMLobj.DeleteRecord('3') == true)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "Character id check\n";
        if (DMLobj.DeleteRecord('a') == false)
        {
            cout << "passed\n";
        }
        else
        {
            cout << "failed\n";
        }

        
        return true;
    }

    bool checkUpdate()
    {
        dbCon.connectDB("myemp", "myPW");
        cout << "*****************************************************************************\n";
        cout << "test cases for update function  check\n";
        cout << "wrong Id  check:\n";
        if (DMLobj.UpdateRecord(21) == false)
        {
            cout << "failed\n";
        }
        else
        {
            cout << "passed\n";
        }
        cout << "Correct Delete ID Check:\n";
        if (DMLobj.UpdateRecord(2) == true)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "wrong Input Character id check\n";
        if (DMLobj.UpdateRecord('a') == false)
        {
            cout << "failed\n";
        }
        else
        {
            cout << "passed\n";
        }


        return true;
        
    }

    bool checksearchbyId()
    {
        dbCon.connectDB("myemp", "myPW");
        cout << "*********************************************************************************\n";
        cout << "test cases for serchByID check\n";
        cout << "special character Id  check:\n";
        if (DQLobj.SearchByID('@') == false)
        {
            cout << "passed\n";
        }
        else
        {
            cout << "Failed\n";
        }
        cout << "Correct serch ID Check:\n";
        if (DQLobj.SearchByID('2') == true)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "wrong Input Character id check\n";
        if (DQLobj.SearchByID('a') == false)
        {
            cout << "passed\n";
        }
        else
        {
            cout << "Failed\n";
        }


        return true;

  }

    bool checkserchByPin()
    {
        dbCon.connectDB("myemp", "myPW");
        cout << "*********************************************************************************\n";
        cout << "test cases for serchByPIN check\n";
        cout << "special character Id  check:\n";
        if (DQLobj.SearchByID('@') == false)
        {
            cout << "passed\n";
        }
        else
        {
            cout << "Failed\n";
        }
        cout << "Correct serch pin Check:\n";
        if (DQLobj.SearchByID('4') == true)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "wrong Input Character id check\n";
        if (DQLobj.SearchByID('a') == false)
        {
            cout << "passed\n";
        }
        else
        {
            cout << "Failed\n";
        }


        return true;



    }

    bool checkinsertfunction()
    {
        dbCon.connectDB("myemp", "myPW");
        cout << "*******************************************************************************\n";
        cout << "test cases for insert record function\n";

        cout << "wrong input for insert check....\n";
        string paraName = "kailas";
        
        if (DMLobj.InsertRecord('a', "kailas", "7517039293", 'b',0,true) == false)
        {
            cout << "Passed\n";
       }
        else
        {
            cout << "Failed\n";
        }


        cout << "special character as input check\n";
        if (DMLobj.InsertRecord('@', "kailas", "7517039293", '#', 0, true) == false)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "Correct input check:\n";
        if (DMLobj.InsertRecord('6', "pratik", "7532009293", 678943, 0, true) == true)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        
        return true;

    }

    bool checkshowrecord()
    {
        dbCon.connectDB("myemp","myPW");
       
        cout << "************************************************\n";
        cout << "test cases for show record function\n";
        cout << "Wrong table name\n";
        if (DQLobj.ShowRecord(0, "abcd") == false)
        {
            cout << "Passed\n";

        }
        else
        {
            cout << "Failed\n";
        }

        cout << "Correct table name\n";
        if (DQLobj.ShowRecord(0, "employee") == true)
        {
            cout << "Passed\n";

        }
        else
        {
            cout << "Failed\n";
        }
        return true;
    }

    bool checkserchbyphoneno()
    {
        dbCon.connectDB("myemp", "myPW");
        cout << "***********************************************\n";
        cout << "Character Phone no check\n ";
        if (DQLobj.SearchByPhoneNo("ASDFGHJHGFG") == false)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "Special character phone no test case \n";
        if (DQLobj.SearchByPhoneNo("#$%^^^&") == false)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "mixed phone no test case\n ";
        if (DQLobj.SearchByPhoneNo("dgfdfh23441#@#") == false)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "Correct phone no test case\n";
        if (DQLobj.SearchByPhoneNo("7517039293") == true)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        return true;

    }

    bool checkcserchbyname()
    {
        dbCon.connectDB("myemp", "myPW");
        cout << "***********************************************\n";
        cout << "numbered Name check\n";
        if(DQLobj.SearchByName("123456")==false)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }
        cout << " special Character Name check\n";
        if (DQLobj.SearchByName("@#$%^&") == false)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "Mixed string Name check\n  ";
        if (DQLobj.SearchByName("dhgfhgf436464@#$%^&") == false)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }
        cout << "Null Name string check\n";
        if (DQLobj.SearchByName(" ") == false)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }

        cout << "Correct Name check\n";
        if (DQLobj.SearchByName("Kailas") == true)
        {
            cout << "Passed\n";
        }
        else
        {
            cout << "Failed\n";
        }


        return true;




    }

    bool checkcreateandtruncate()
    {
        cout << "**********************************************************\n";
        dbCon.connectDB("myemp", "myPW");
        utest = true;

        cout << "Numbered table name test\n";
        if (CTobj.CreateTable("23456781") == false)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }

        cout << "Empty table Name test check\n";
        if (CTobj.CreateTable(" ") == false)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }

        cout << " table already exists test check\n";
        if (CTobj.CreateTable("employee") == false)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }
        cout << "Special character table name given\n";
        if (CTobj.CreateTable("$%^&") == false)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }

        cout << " New and Correct Table name given\n";
        if (CTobj.CreateTable("project") == true)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }

        cout << "Test cases for Truncate\n";

        cout << "Numbered table name test\n";
        if (CTobj.TruncateTable("23456781") == false)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }
        cout << "Empty table Name test check\n";
        if (CTobj.TruncateTable(" ") == false)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }

        cout << "Table Not exists test check\n";
        if (CTobj.TruncateTable("abcd") == false)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }
        cout << "Special character table name given\n";
        if (CTobj.TruncateTable("$%^&") == false)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }

        cout << "Correct Table name given\n";
        if (CTobj.TruncateTable("project") == true)
        {
            cout << "Passed" << endl;

        }
        else
        {
            cout << "failed\n";
        }


        return true;
    }

    bool checktabledata()
    {
        dbCon.connectDB("myemp", "myPW");
        cout << "******************************************************************\n";
        cout << "wrong database test case\n";
        if (Vobj.tableData("employee", "abcd")==false)
        {
            cout << "Passed\n";

        }
        else
        {
            cout << "Failed\n";
        }
        cout << "wrong table test case\n";
        if (Vobj.tableData("abcd", "Record") == false)
        {
            cout << "Passed\n";

        }
        else
        {
            cout << "Failed\n";
        }
        cout << "wrong table and database test case\n";
        if (Vobj.tableData("abcd", "abcd") == false)
        {
            cout << "Passed\n";

        }
        else
        {
            cout << "Failed\n";
        }

        cout << "correct table and database test case\n";
        if (Vobj.tableData("employee", "Record") == true)
        {
            cout << "Passed\n";

        }
        else
        {
            cout << "Failed\n";
        }



        return true;
    }

    bool checkReplicate()
    {

        dbCon.connectDB("myemp", "myPW");
        cout << "******************************************************************\n";
        cout << "wrong destination database check\n";

       if(dbCon.replicate("employee", "record", "abcdf")==false)
       {
           cout << "Passed\n";

       }
       else
       {
           cout << "Failed\n";
       }

       cout << "Wrong source database check\n";
       if (dbCon.replicate("employee", "dghhfhdh", "employee") == false)
       {
           cout << "Passed\n";

       }
       else
       {
           cout << "Failed\n";
       }

       cout << "wrong source table check\n";
       if (dbCon.replicate("12sdaadd", "record", "employee") == false)
       {
           cout << "Passed\n";

       }
       else
       {
           cout << "Failed\n";
       }


       return true;
    }

    void executeUnitTestCases()
    {
        utest = true;
      // if (CheckConnection() == true)
      //     cout << "DB Connection Test Case Passed\n";
      //   if(testCheckTable() == true)
      //      cout << "TableCheck test cases passed\n";
      //  if (checkDeleteRecord() == true)
      //     cout << "Delete function test case passed\n";

      //// if (checkUpdate() == true)
      //    //cout << "update function test case passed\n";

      //  if (checksearchbyId() == true)
      //     cout << "search by id test case passed\n";
      //if (checkserchByPin() == true)
      //      cout << "search by pin test cases passed\n";
      //  if (checkinsertfunction() == true)
      //     cout << "insert function test case passed\n";

      //  if (checkshowrecord() == true)
      //  {
      //      cout << "show record checked\n";
      //  }

       // if (checkserchbyphoneno() == true)
          //  cout << "serch by phone no test checked \n";

       /* if (checkcserchbyname() == true)
        {
            cout << "Serch By Name test checked\n";
       }*/

        
       /* if (checkcreateandtruncate() == true)
            cout << "Create And Truncate Function is checked\n";*/

        /*if (checktabledata() == true)
        {
            cout << "cheked successfully\n";
        }*/


        if (checkReplicate() == true)
        {
            cout << "cheked successfully\n";
        }
    }
};
