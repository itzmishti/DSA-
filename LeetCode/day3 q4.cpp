class Solution {
public:
    void remove(std::vector<int> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
 
    v.erase(end, v.end());
}
    vector<int> majorityElement(vector<int>& nums) {
        int n=nums.size();
        map<int,int>h;
        vector<int>v;
        //int ans=0;
       // int ind=0;
        for(auto i=0;i<nums.size();i++)
        {
            h[nums[i]]++;
            if((n/3)<h[nums[i]]) v.push_back(nums[i]);
                            
        }
        remove(v);
        return v ;
        
    }
};