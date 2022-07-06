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



int lengthLL(Node *head)
{
    Node *temp=head;
    int count=0;
    while(temp!=NULL)
    
    {
        count++;
        temp=temp->next;
    }
    return count;
}
Node* appendk(Node *&head,int k)
{
    Node *tail=head;
    Node *newHead;
    Node *newTail;
    int l=lengthLL(head);
    k=k%l;
    int count=1;
    while(tail->next!=NULL)
    {
        if(count==l-k) 
        {
            newTail=tail;
        }
        if(count==l-k+1)
        {
            newHead==tail;
        }
        tail=tail->next;
        count++;
    }
    newTail->next=NULL;
    tail->next=head;
    
    
    return newHead;
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
    display(head);
    Node *newHead=appendk(head,3);
    display(newHead);
    return 0;
}



