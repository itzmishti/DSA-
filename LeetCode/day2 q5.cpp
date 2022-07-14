vector<int> Solution::repeatedNumber(const vector<int> &A) {
 
    long n1=A.size();
    long m[n1+1]={0};
    vector<int>len1(2);
    for(auto i:A)
    {
        m[A[i]]++;
    }
    for(long i=1;i<=n1+1;i++)
    {
        if(m[i]==2) len1[0]=i;
        
        else if(m[i] !=1) len1[1]=i;
    }
    
    return len1;
}