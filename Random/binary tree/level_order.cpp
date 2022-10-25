/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == NULL) return ans;
        
        queue<TreeNode*> q;
        
        q.push(root);
        
        
        while(!q.empty())
        {
            int num = q.size();
            vector<int> level;
            while(num--)
            {
                TreeNode* elem = q.front();
                q.pop();
                if(elem->left != NULL)  q.push(elem->left);
                if(elem->right != NULL) q.push(elem->right);
                level.push_back(elem->val);
            }
            ans.push_back(level);
        }
        return ans;
    }
};