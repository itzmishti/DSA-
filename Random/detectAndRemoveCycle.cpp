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
bool detectCycle(Node *&head)
{
    Node *slow=head;
    Node *fast=head;
    while(fast!=NULL && fast->next!=NULL)
    {
        slow=slow->next;
        fast=fast->next->next;
        if(fast==slow)
        {
            return true;
        }
    }
    return false;
}

void removeCycle(Node *&head)
{
    Node *fast=head;
    Node *slow=head;
    do
    {
        slow=slow->next;
        fast=fast->next->next;
    }while(slow!=fast);
    
    fast=head;
    while(fast->next!=slow->next)
    {
        fast=fast->next;
        slow=slow->next;
    }
    slow->next=NULL;

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
    cout<<detectCycle(head);
    return 0;
}

