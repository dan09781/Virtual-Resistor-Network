#include "NodeList.h"

using namespace std;

NodeList::NodeList()  //default constructor
{
    head = NULL;
}

NodeList::~NodeList()  //destructor
{
    while (head!=NULL)
    {
        Node* tptr;
        tptr=head;
        head=tptr->getNext();
        delete tptr;
    }
}


bool NodeList::insert (Node* ptr) //sorted insert for nodes
{
    int tID = ptr->getID();
    Node *current = head;
    Node *previous = NULL;
    while (current != NULL && (current->getID()) < tID)
    {
        previous = current;
        current = current -> getNext ();
    } 
    ptr->setNext (current);
    if (previous == NULL)
        head = ptr;
    else
        previous->setNext (ptr);
    return true;
}

bool NodeList::deleteNode(int nodeID) //delete node
{
    Node *current = head;
    Node *previous = NULL;
    while (current != NULL && current->getID()!=nodeID)
    {
        previous = current;
        current = current -> getNext();
    }
    if (current == NULL) return false;
    if (previous == NULL)
        head = current->getNext ();
    else
        previous->setNext (current->getNext());
    delete current;
    return true;
}

Node* NodeList::getHead()
{
    return head;
}

Node* NodeList::setHead(Node* ptr)
{
    head=ptr;
}