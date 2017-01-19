#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"

using namespace std;

ResistorList::ResistorList () //default constructor
{
    head = NULL;
}

ResistorList::~ResistorList() //destructor
{
    while (head!=NULL)
    {
        Resistor* tptr;
        tptr=head;
        head=tptr->getNext();
        delete tptr;
    }
}

Resistor* ResistorList::getHead () //accessor
{
    return head;
}

bool ResistorList::insertResistor (Resistor* ptr) //insert resistor into resistor list
{
    if (head==NULL)
        head=ptr;
    else{
        Resistor *tptr=head;
        while (tptr->getNext()!=NULL)
            tptr=tptr->getNext();
        tptr->setNext(ptr);
    }
    return true;
}

Resistor* ResistorList::setHead(Resistor* ptr) //mutator
{
    head=ptr;
}