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
/*
Inorder traversal stores or displays the array in left->root->right order
For binary search trees it displays the list of numbers in ascending order
*/
class Solution {
public:   
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        
        inorder(root,ans);
        return ans;     
        
    }
    
    void inorder(TreeNode* root,vector<int> &ans){
        if(!root){
            return;
        }       
        
        inorder(root->left,ans);
        ans.push_back(root->val);
        inorder(root->right,ans);
    }
};