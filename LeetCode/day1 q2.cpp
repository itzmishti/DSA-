class Solution {
public:
    vector<vector<int>> generate(int n) {
      
        vector< vector< int > > ans( n );
    
    ans[ 0 ].push_back( 1 );
    if( n == 1 )
        return ans;
    
    ans[ 1 ].push_back( 1 );
    ans[ 1 ].push_back( 1 );
    if( n == 2 )
        return ans;
    
    for( int i = 2; i < n; i++ ) {

        for( int j = 0; j <= i; j++ ) {
            
            if( j == 0 or j == i )
                ans[ i ].push_back( 1 );
            else
                ans[ i ].push_back( ans[ i - 1 ][ j - 1 ] + ans[ i - 1 ][ j ] );
            
        }
        
    }
    
    return ans;
    //r-1 C c-1 gives the reqired element at the index position
}

};


//Method 2
class Solution {
public:
    vector<vector<int>> generate(int n) {
      
        vector< vector< int > > ans( n );
    
    for(int i=0;i<n;i++)
    {
        ans[i].resize(i+1);
        ans[i][0]=ans[i][i]=1;
        
        for(int j=1;j<i;j++)
        {
            ans[i][j]=ans[i-1][j-1]+ans[i-1][j];
        }
    }
    return ans;
    
}

};
