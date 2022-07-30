#include <bits/stdc++.h>
using namespace std;

//Binary tree from pre order

//int index=0;

class node
{
    public:
    int data ;
    node *left;
    node *right;
    
    node(int val)
    {
        data=val;
        left=NULL;
        right=NULL;
    }
};

// node* binaryTree(node *nodes,int index)
// {
//     index++;

//     if(nodes[index] ==-1) return NULL;
    
//     node *newNode=new node(nodes[index]);

//     newNode->left=binaryTree(nodes,index);
//     newNode->right=binaryTree(nodes,index);
    
//     return newNode;
// }

void preorder(node *root)
{
    if(root==NULL) return;
    
    cout<<root->data<<"  ";
    preorder(root->left);
    preorder(root->right);
}

//level order transversal

void levelorder(node *root)
{
    if(root==NULL) return;
    queue<node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty())
    {
        node *curr=q.front();
        q.pop();
        if(curr !=NULL) 
        {
            cout<<curr->data<<" ";
              if(curr->left!=NULL) q.push(curr->left);
                if(curr->right!=NULL) q.push(curr->right);
        }
        else if(!q.empty())
        {
            q.push(NULL);
            
        }
        
    }
}

//Sum of the nodes at the Kth level
int sumK(node *root,int k)
{
    if(root==NULL) return -1;
    queue<node *>q;
    q.push(root);
    q.push(NULL);
    int level=0;
    int sum=0;
    
     while(!q.empty())
     {
        node *curr=q.front();
        q.pop();
        if(curr != NULL)
        {
            if(level==k)
            sum=sum+curr->data;
            
            if(curr->left !=NULL) q.push(curr->left);
            if(curr->right !=NULL) q.push(curr->right);
        }
        
        else if(!q.empty())
        {
         q.push(NULL);
         level++;
        }
     }
    
    return sum;
}

int main()
{
    //int nodes[]={1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
    node *root=new node(1);
    root->left=new node(2);
    root->right=new node(3);
    root->left->left=new node(4);
    root->left->right=new node(5);
    root->right->right=new node(6);
    int index=-1;

   // node *head=binaryTree(root,index);
    cout<<root->data<<endl;
    preorder(root);
    cout<<endl;
    levelorder(root);
    int ans=sumK(root,2);
    cout<<endl;
    cout<<ans;
    return 0;
}
//     1 
//   2    3
//  4 5  _   6
