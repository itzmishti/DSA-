class Solution {
public:
    void sortColors(vector<int>& nums) {
        
        int z,o,t;
        z=o=t=0;
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]==0) z++;
            else if (nums[i]%2==1) o++;
            else t++;
        }
        for(int i=0;i<z;i++) nums[i]=0;
        for(int i=0;i<o;i++) nums[i+z]=1;
        for(int i=0;i<t;i++) nums[i+z+o]=2;


        
    }
};