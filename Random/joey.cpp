#include <bits/stdc++.h>
using namespace std;

int count(string s,char c)
{
    int count=0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] ==  c)
        {
            count++;
        }
    }
    return count;
}
//Approach:Just count the special characters like w in two x in six
int sumOfString(string s)
{
    int zero,one,two,three,four,five,six,seven,eight,nine;
    zero=count(s,'z');
    two=count(s,'w');
    four=count(s,'u');
    five=count(s,'f')-four;
    six=count(s,'x');
    seven=count(s,'s')-six;
    eight=count(s,'g');
    nine=count(s,'i')-five-six-eight;
    one=count(s,'o')-zero-two-four;
    three=count(s,'r')-zero-four;
    
    int sum=one+2*two+3*three+4*four+5*five+6*six+7*seven+8*eight+9*nine;
    return sum;
    
}
int main()
{
    string s;
    cin>>s;
    int ans=sumOfString(s);
    cout<<ans;
    return 0;
}
