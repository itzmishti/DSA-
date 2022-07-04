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




Node *reversek(Node *&head,int k)
{
    Node *nextptr,*prev=NULL;
    Node *curr=head;
    int count=0;
    while(count<k && curr!=NULL)
    {
        nextptr=curr->next;
        curr->next=prev;
        prev=curr;
        curr=nextptr;
        count++;
    }
    if(nextptr!=NULL)
    {
    head->next=reversek(nextptr,k);

    }
    return prev;
}

int main()
{
    Node *head=NULL;
    insertAtTail(head,1);
    insertAtTail(head,2);
    insertAtTail(head,3);
    insertAtTail(head,4);
    insertAtTail(head,5);
    insertAtTail(head,6);
    insertAtTail(head,7);
    insertAtTail(head,8);
    
int k=2;
Node *newHead=reversek(head,k);
display(newHead);
    return 0;
}

