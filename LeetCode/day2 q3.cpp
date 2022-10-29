class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    
    int k=0;
    for(int i=m;i<=m+n-1;i++)
    {
       nums1[i] =nums2[k];//adds element to end of first array
        k++;
    }
    sort(nums1.begin(),nums1.end());
    }
};