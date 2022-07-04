#include <iostream>
using namespace std;

class Node
{
    public:
    int data;
    Node *next;
    
    Node(int val){
        data=val;
        next=NULL;
    }
};
bool findKey(Node *head,int key)
{
    Node *temp=head;
    while(temp!=NULL)
    {
        if(temp->data==key) return true;
        temp=temp->next;
    }
    return false;
}

void insertAtTail(Node * &head,int val)
{
    Node *n=new Node(val);
    if(head==NULL) 
    {
        head=n;
        return;
    }
    Node *temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=n;
    
}

void insertAtHead(Node *&head,int val)
{
    Node *n =new Node(val);
    n->next=head;
    head=n;
}

void display(Node *head)
{
    Node *temp=head;
    while(temp!=NULL)
    {
        cout<<temp->data<<"->";
        
        temp=temp->next;
    }
    cout<<"NULL"<<endl;
}
void deletionAtHead(Node*&head)
{
    Node *toDelete=head;
    head=head->next;
    delete toDelete;
}

void deletion(Node * &head,int val)
{
    if(head==NULL) return;
    if(head->next==NULL) 
    {
        deletionAtHead(head);
        return;
    }
    Node *temp=head;
    while(temp->next->data!=val)
    {
        temp=temp->next;
    }
    Node *toDelete=temp->next;
    temp->next=temp->next->next;
    delete toDelete;
}
Node* reversing(Node *&head)
{
    Node *curr=head;
    Node *prev=NULL,*nextptr=NULL;
    while(curr!=NULL)
    {
        nextptr=curr->next;
        curr->next=prev;
        prev=curr;
        curr=nextptr;
        
    }
    return prev;
}
Node* reverseRecursive(Node*&head)
{
    
    if(head==NULL || head->next==NULL)
    {
        return head;
    }
    Node *newHead=reverseRecursive(head->next);
    head->next->next=head;
    head->next=NULL;
    
    return newHead;
}

int main()
{
    Node *head=NULL;
    insertAtTail(head,1);
    insertAtTail(head,2);
    insertAtTail(head,3);
    display(head);
    insertAtHead(head,6);
    display(head);
    
    cout<<findKey(head,2)<<endl;
    cout<<findKey(head,5)<<endl;
    deletion(head,2);
    display(head);
    // Node *newHead=reversing(head);
    // display(newHead);
    Node *newHead2=reverseRecursive(head);
    display(newHead2);

    return 0;
}
