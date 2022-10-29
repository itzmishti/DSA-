#include <iostream>
#include <string>
using namespace std;
/*program assigns factions according to popular movie series divergent*/
int main()
{
    int x,y,z,c;
    
    cout<<"Enter an integer"<<endl;
    cin>>c;
    cout<<"Enter an integer"<<endl;
    cin>>x;
    if(x<=500)
    cout<<"\nDauntless\n";
    cout<<"Enter an interger"<<endl;
    cin>>y;
    if(y<=200)
    cout<<"\nAmity\n";
    else
    cout<<"\nCandor\n";
    cout<<"Enter an integer"<<endl;
    cin>>z;
    if(z==16)
    cout<<"\nDivergent\n";
    else if(z==2)
    cout<<"\nFactionless\n";
    else if(z==1)
    cout<<"\nFactionless\n";
    
    switch(c)
    {
        case 1: cout<<"\nAbnegation";
		break;
        case 2: cout<<"\nErudite";
		break;
        default : break;
    }
    return 0;
}

