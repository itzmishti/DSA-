class Solution {
public:
    int maxProfit(vector<int>& nums) {
        int n=nums.size();
        int maxP=0;
        
        int m=INT_MAX;
        for(int i=0;i<n;i++)
        {
           m=min(m,nums[i]);
            maxP=max(maxP,nums[i]-m);
        }
        
        return maxP;
    }
};