#include "std_lib_facilities.h"
 
//9.4.1 - simple Date
struct Date
{
 int y;  //year
 int m;  //month
 int d;  //day
};

Date today;
Date tomorrow;

//initialise the day
void init_day(Date& dd, int y, int m, int d)
{
 if (y < 1900 || y > 2021)
  cout << "Error, invalid year." << endl;
 else if (m < 1 || m > 12)
  cout << "Error, invalid month." << endl;
 else if (d < 1 || d > 31)
  cout << "Error, invalid day." << endl;
 else
 {
  //if date is valid, initalise the date
  dd.y = y;
  dd.m = m;
  dd.d = d;
 }

 return;
}

//increment date by n days
void add_day(Date dd, Date& dd_copy, int n)
{
 bool lastDay = false;
 bool endYear = false;

 //if day go above 31, increase month, set day to 1
 //if month goes above 12, increase year, set month to 1
 for (int i = 0; i < n; ++i)
 {
 
  if (dd.d == 31)
   lastDay = true;
  dd.d = (dd.d == 31) ? 1 : ++dd.d;

  if (lastDay)
  {
   
   lastDay = false;
   dd.m = (dd.m == 12) ? 1 : ++dd.m;
   if (dd.m == 12)
    endYear = true;

   if (endYear)
   {
    
    endYear = false;
    ++dd.y;
   }

  }
  
 }

 //assign tomorrow with copy of modified today
 dd_copy = dd;
}

//print to screen
ostream& operator<<(ostream& os, const Date& d)
{
 return os << d.d << ", " << d.m << ", " << d.y << endl;
}

int main()
{
 //initialise today with June 25 1978
 init_day(today, 1978, 6, 25);

 //assign by copying and increase by 1 day
 add_day(today, tomorrow, 1);

 //print out results
 cout << "Today: " << today << endl;
 cout << "Tomorrow: " << tomorrow << endl;

 keep_window_open();

 return 0;
}
