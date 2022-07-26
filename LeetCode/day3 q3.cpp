class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n=nums.size();
        map<int,int>h;
        int ans=0;
        int ind=0;
        for(auto i=0;i<nums.size();i++)
        {
            h[nums[i]]++;
            if(ans<h[nums[i]]) ind=nums[i];
            
            ans=max(ans,h[nums[i]]++);
                
        }
        return ind ;
    }
};
