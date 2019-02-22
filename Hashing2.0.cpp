//-|-----------------------------------------------------------------------
//-| File name: Hashing2.0.cpp
//-| Assign ID: PROG4.1
//-| 
//-|Project  Hashing (part 1)  DUE Feb. 21 2019  at 12:30pm  DO NOT USE VECTORS
//-|
//-|Write a C++ program that inputs an unknown number of records from a sequential file.
//-|
//-|Use the following structure definition in your program.
//-|
//-|Write a C++ program to create a hash table (containing 137  slots  to store records) 
//-|store the records using account_num as the key field.
//-| Use the method called linear probing to handle collisions.   
//-|Compute the salary increase for each employee based on the following scale:
//-|
//-|10% for years of service 20 or greater but less than 30
//-|5.2% for years of service 10 or greater but less than 20
//-|3.4% for years of services less than 10
//-|15.89% for years of service 30 or more.                  
//-|                  
//-| Author:Sony Jean-Baptiste
//-|
//-|-------------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <queue>
#include <cctype>
#include <map>
#include <ctime>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

//-|---------------------------------------------------------------------------
//-| PRINT student copyright.
//-|---------------------------------------------------------------------------
void Display_Copyright()
{
cout << endl << "(c) 2019,Sony Jean-Baptiste" << endl << endl;
}//-|Display_Copyright


//-|---------------------------------------------------------------------------
//-| Setting the size of table (size of table is use for mod index key).
//-|---------------------------------------------------------------------------
const int tableSize = 50;

//-|---------------------------------------------------------------------------
//-| Record file format.
//-|---------------------------------------------------------------------------
struct RECORD 
{
    
string last_name;
string first_name;
unsigned account_num;    //KEY field
unsigned month;
unsigned day;
unsigned year;
float annual_salary;
char dept_code;  
string phone_number;

};

//-|---------------------------------------------------------------------------
//-| Creating the hash based on the size of the table
//-|   initializing the index based on the key(account_num).
//-|---------------------------------------------------------------------------
class createHash 
{
  public: 
  RECORD hashtable[tableSize];
  
  int hash (int key)
  {
  int index = key % tableSize; // account_num % tableSize(50)
  return index;      
  };
    
//-|---------------------------------------------------------------------------
//-| Display hash to the out file.
//-|---------------------------------------------------------------------------  
 void displayHash(ostream &outF, int count);
    
//-|---------------------------------------------------------------------------
//-| Initializing the  Hash Table that is created.
//-| .
//-|---------------------------------------------------------------------------  
  createHash()
  {
     for(int i = 0; i < tableSize; i++)
     {
         hashtable[i].last_name = "0";
         hashtable[i].first_name = "0";
         hashtable[i].account_num = 0;
         hashtable[i].month = 0;
         hashtable[i].day = 0;
         hashtable[i].year = 0;
         hashtable[i].annual_salary = 0;
         hashtable[i].dept_code = 0;
         hashtable[i].phone_number = "0";         
     
     }
  };
    
//-|---------------------------------------------------------------------------
//-| Inserting the each RECORD in the the table according to account_num.
//-|---------------------------------------------------------------------------  
      bool insert(RECORD sony) //RECORD 
      {
          int i = hash(sony.account_num);
          if(hashtable[i].first_name == "0")
          {
              hashtable[i].last_name = sony.last_name;
              hashtable[i].first_name = sony.first_name;
              hashtable[i].account_num = sony.account_num;
              hashtable[i].month = sony.month;
              hashtable[i].day = sony.day;
              hashtable[i].year = sony.year;
              hashtable[i].annual_salary = sony.annual_salary;
              hashtable[i].dept_code = sony.dept_code;
              hashtable[i].phone_number = sony.phone_number;
              return false;             
          }
          //array[ hashtable[i].day]
          else
          {
              int initIndex = i;
              int j;
              if (i = tableSize-1)
              {
                 i=0;
                 j=i;
              }
              else
              {
                  j=i+1;
              }
              for (j; j<tableSize; j++)
              {
                  if(j == tableSize-1 && hashtable[j].first_name != "0")
                  {j = 0;}
                  hashtable[j].last_name = sony.last_name;
                  hashtable[j].first_name = sony.first_name;
                  hashtable[j].account_num = sony.account_num;
                  hashtable[j].month = sony.month;
                  hashtable[j].day = sony.day;
                  hashtable[j].year = sony.year;
                  hashtable[j].annual_salary = sony.annual_salary;
                  hashtable[j].dept_code = sony.dept_code;
                  hashtable[j].phone_number = sony.phone_number;
                  return false;
              }
              if(j == initIndex)
              {
                  cout << "TABLE IS AT MAX CAPACITY!!" << endl; 
                  return true;
              }
          }
          
      }
     
  };//Inserting the each RECORD in the the table according to account_num.

//-|---------------------------------------------------------------------------
//-| Read the data from the file thats given.
//-|---------------------------------------------------------------------------
bool readDataFromFile(ifstream & inF, RECORD &temp);



//-|---------------------------------------------------------------------------
//-| Display Hash table.
//-|---------------------------------------------------------------------------
void createHash::displayHash(ostream &outF, int count) // add all of the field(total)
{
    unsigned year;
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);//current time
    unsigned cyr = timePtr->tm_year+1900;// current year
    int name_width = 15;
    string mnth[12] = {"Jan. ", "Feb. ", "Mar. ", "Apr. ", "May. ", "Jun. ", 
                       "Jul. ", "Aug. ", "Sept. ", "Oct. ", "Nov. ", "Dec. "};
    unsigned Minute = timePtr -> tm_min;
    unsigned Year = timePtr -> tm_year+1990;
    unsigned Hour = timePtr -> tm_hour-4;
    unsigned Day = timePtr -> tm_mday;
    unsigned Month = timePtr -> tm_mon+1;
    
    
    
     outF << setw(45) << "Employee Report" << setw(20) << "Date: " << Month << "/" << Day << "/" << Year << endl;

     outF << setw(45) << "***************" << setw(20) << "Time: " << Hour << ":" << Minute << endl << endl;

outF << "Last" << setw(15) << "Acct" << setw(20) << "Date Of" << setw(15) << "Annual" << setw(18) << "Salary" << setw(20) << "Department" << setw(25) << "Years of" << endl;

outF << "Name" << setw(15) << "Number" << setw(20) << "Birth" << setw(15) << "Salary" << setw(17) << "Increase" << setw(20) << "Code" << setw(25) << "Service" << endl << endl;
    
   int i = 0; 
    float sum = 0;
    float total = 0;
    for(i; i<tableSize; i++)
        {
        if(hashtable[i].first_name == "0"){continue;}
            // count++;
            float salary_increase = 0;
        stringstream ss;
        ss << hashtable[i].account_num;
        string an = ss.str();
            int service = cyr - hashtable[i].year;
            outF << setw(15) << left << hashtable[i].last_name << setw(15);
        if(hashtable[i].account_num < 1000 && hashtable[i].account_num >= 100)
        {
            outF << setw(15) << "0"+an;
        }
        if(hashtable[i].account_num < 100 && hashtable[i].account_num >= 10)
        {
            outF << setw(15) << "00"+an;
        }
        if(hashtable[i].account_num < 10)
        {
            outF << setw(15) << "000"+an;
        }
        if(hashtable[i].account_num  == 0)
        {
            outF << setw(15) << "0000";
        }
        if(hashtable[i].account_num  > 1000)
        {outF << setw(15) << an;
        }
            outF << hashtable[i].month << " " << hashtable[i].day << "," << setw(4) << setfill('0') << hashtable[i].year << setfill(' ') << "         ";
            outF << "$"  << setw(15) << setprecision(2) << fixed << hashtable[i].annual_salary;
            if (service >= 20 && service < 30)
            {
                salary_increase = hashtable[i].annual_salary * .1;
            }
            if (service >= 10 && service < 20)
            {
                salary_increase = hashtable[i].annual_salary * .052;
            }
            if (service < 10)
            {
                salary_increase = hashtable[i].annual_salary * .034;
            }
            if (service >= 30)
            {
                salary_increase = hashtable[i].annual_salary * .1589;
            }
            outF << "$" << setw(17) << setprecision(2) << fixed << salary_increase << setw(15);
            outF << hashtable[i].dept_code << setw(20);
            outF << service << endl; //i++;
            sum += hashtable[i].annual_salary;
            total += salary_increase;
            
        }
           
      
    outF << endl << "Total Line                                     $" << sum << "        $" << total << endl;
    outF << "Total record count: " << count;
   

}// display  

 


//main
int main() 
{
   ifstream inF;
   ofstream outF;
   inF.open("hashdata1.txt");
   createHash ch; 
   RECORD r;
//-|-----------------------------------------------------------------------
//-|  Display copyright.
//-|-----------------------------------------------------------------------
    Display_Copyright();
    
   int count = 0;
   while (inF >> r.account_num >> r.first_name >> r.last_name >> r.month >> r.day >> r.year >> r.annual_salary 
          >> r.dept_code >> r.phone_number)
   {
       ch.insert (r);
   }
    
    inF.close();
    
    outF.open("results Report");
    ch.displayHash(outF, count);
    outF.close();
             
        
        return 0;
}