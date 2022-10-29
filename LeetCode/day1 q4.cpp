class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum=INT_MIN;
        int curr=0;
        for(int i=0;i<nums.size();i++)
        {
            curr=curr+nums[i];
            maxSum=max(curr,maxSum);//check bigger element
            if(0>curr)
                curr=0;
        }
        return maxSum;//returns biggest subarray
    }
};