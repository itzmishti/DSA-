#include <iostream>
using namespace std;
class base
{
	
};
class derived:public base
{
	
};

//baseObj is caught if derObj is thrown if the catch of base is written before try of derived class
//try of der does not catch obj of base
int main() 
{
	base baseObj;
	derived derObj;
	try
	{
		throw baseObj;
	}
	
	catch(base baseObj)
	{
		cout<<"Caught baseObj"<<endl;
	}
	catch(derived derObj)
	{
		cout<<"Caught derObj"<<endl;
	}
	try
	{
		throw derObj;
	}

	catch(derived derObj)
	{
		cout<<"Caught derObj"<<endl;
	}
		catch(base baseObj)
	{
		cout<<"Caught baseObj"<<endl;
	}
	

	return 0;
}
