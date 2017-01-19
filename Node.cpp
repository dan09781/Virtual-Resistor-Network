#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"

using namespace std;

Node::Node(int nodeID) //constructor
{
    id = nodeID; 
    voltage = 0;
    next = NULL;
    numRes = 0;
    res = new ResistorList();
    setV = false;
}

Node::Node(int nodeID, double v) //overloaded constructor
{
    id = nodeID;
    voltage = v;
    next = NULL;
    numRes = 0;
    res = new ResistorList();
    setV = true;
}

Node::~Node(){  //destructor for node
    while (res->getHead()!=NULL)
    {
        Resistor* tptr;
        tptr=res->getHead();
        res->setHead(tptr->getNext());
        delete tptr;
    }
    delete res;
}

void Node::setVoltage(double v) //mutator
{
    voltage = v;
}

double Node::getVoltage () //accessor
{
    return voltage;
}

int Node::getID() //accessor
{
    return id;
}

Node* Node::getNext() //accessor
{
    return next;
}

void Node::setNext (Node *n) //mutator
{
    next = n;
}

ResistorList* Node::getResList () //accessor
{
    return res;
}

int Node::getNumRes() //accessor
{
    return numRes;
}

void Node::incNumRes()   //mutator
{
    numRes ++;
}
void Node::setNumRes(int n) //mutator
{
    numRes=n;
}

void Node::decNumRes() //mutator
{
    numRes--;
}

bool Node::setVCheck () //accessor
{
    return setV;
}

void Node::setVSetTrue () //mutator
{
    setV = true;
}

void Node::setVSetFalse () //mutator
{
    setV = false;
}

