#include "std_lib_facilities.h"
 
struct Date
{
 int y, m, d;   //year, month, day
 Date(int y, int m, int d); //check for valid date and initialise
 void add_day(int n);  //increase the Date by N days
};

//intialise dates
Date today(1978, 6, 25);
Date tomorrow(today);

//Date Constructor - initialise the day
Date::Date(int y, int m, int d)
{
 //check that y m d is a valid date
 if (y < 1900 || y > 2021)
  cout << "Error, invalid year." << endl;
 else if (m < 1 || m > 12)
  cout << "Error, invalid month." << endl;
 else if (d < 1 || d > 31)
  cout << "Error, invalid day." << endl;
 else
 {
  //if date is valid, initalise the date
  Date::y = y;
  Date::m = m;
  Date::d = d;
 }

 return;
}

//increment date by n days
void Date::add_day(int n)
{
 bool lastDay = false;
 bool endYear = false;

 //if day goes above 31, increase month, set day to 1
 //if month goes above 12, increase year, set month to 1
 for (int i = 0; i < n; ++i)
 {
 
  if (Date::d == 31)
   lastDay = true;
  Date::d = (Date::d == 31) ? 1 : ++Date::d;  //if day is equal to 31, make it 1, otherwise ++

  if (lastDay)
  {
   
   lastDay = false;
   Date::m = (Date::m == 12) ? 1 : ++Date::m; //if month is equal to 12, make it 1, otherwise ++
   if (Date::m == 12)
    endYear = true;

   if (endYear)
   {
    //just increase year by one
    endYear = false;
    ++Date::y;
   }

  }
  
 }
}

//print to screen
ostream& operator<<(ostream& os, const Date& d)
{
 return os << d.d << ", " << d.m << ", " << d.y << endl;
}

int main()
{
 //increase day by one
 tomorrow.add_day(1);

 //print out results
 cout << "Today: " << today << endl;
 cout << "Tomorrow: " << tomorrow << endl;

 keep_window_open();

 return 0;
}
