class Solution {
public:
    void nextPermutation(vector<int>& nums) 
    {
        
        int n=nums.size();
        
        if(n==0 || n==1) return;
        
        int ind1,ind2;
        int i;
        
        for(int i=n-2;i>=0;i--)
        {
            if(nums[i]<nums[i+1])
            {
                        ind1=i;

                break;
            }
        }
        if(ind1<0) reverse(nums.begin(),nums.end());
        
     
else{
    sort(nums.begin()+ind1+1,nums.end(),greater<int>());

        for( i=n-1;i>ind1;i--)
        {
            if(nums[i]>nums[ind1] )
            {
                        ind2=i;

                break;           
            }      
        }
        swap(nums[ind1],nums[ind2]);
        sort(nums.begin()+ind1+1,nums.end());

        //reverse(nums.begin()+ind1+1,nums.end());
        return ;
        }
    }
};