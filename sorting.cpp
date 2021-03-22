#include "std_lib_facilities.h"
int main()
{
int V[8]={55555,777777777,2,11,84,1,9,83};
int j, i, key;
for (j=1;j<8;j++){
	i=j-1;
	key=V[j];
	while (i>-1 && V[i]>key)
	{
	V[i+1]=V[i];
	i=i-1;}
	V[i+1]=key;

}

for (int k=0; k<8; k++){
cout<< V[k]<<' ';
}
return 0;
}
