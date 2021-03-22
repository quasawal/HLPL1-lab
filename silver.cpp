#include "std_lib_facilities.h"

int main()
{
double C_weight, C_purity, metal_price, usdtohuf;

// we get price of metal in huf per gram
 

cout <<"enter price of silver or gold per ounce in usd\n";

 cin >>metal_price;

 metal_price/=31.1035;

cout<<"enter HUF per USD\n";

cin>> usdtohuf;

metal_price*=usdtohuf;

cout<<metal_price<<"forint per gram\n";

//we get coin weight and purity

cout << "Enter weight of metal in grams\n";
cin>>C_weight;
cout << "Enter purity\n";
cin >> C_purity;
cout <<"this item has"<<C_weight * C_purity << "grams of pure metal\n" << "The Cost is " << metal_price * C_weight * C_purity;




	return 0;

}
