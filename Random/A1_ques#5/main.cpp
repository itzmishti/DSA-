#include <iostream>
using namespace std;
int main()
{
    int i;
    for(i=0;i<5;i++)
    {
    	cout<<"i\n";
	}
    
    while(i>=0)
    {
        cout<<"Hey\n";
        i--;
    }
    
    do
    {  cout<<"Hello\n";
        i++;
    }
	while(i<=5);
     
	return 0;
}

