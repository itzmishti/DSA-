
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
    int maxDepth(TreeNode* root) {
        queue<TreeNode*> q;
        int ans=0;
        if(root==NULL)  return ans;
        q.push(root);
        while(!q.empty())
        {
            ans++;
            int num = q.size();
            
            while(num--)
            {
                TreeNode* node= q.front();
                q.pop();
                if(node->right!=NULL)   q.push(node->right);
                if(node->left!=NULL)   q.push(node->left);
            }
        }
        return ans;
    }
};