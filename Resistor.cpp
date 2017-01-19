#include "Resistor.h"

using namespace std;

Resistor::Resistor(double res, string rName, int IDs[2]) //constructor
{
    resistance = res;
    name = rName;
    endPoints[0] = IDs[0];
    endPoints[1] = IDs[1];
    next = NULL;
}

Resistor::~Resistor(){ //destructor
   
}

string Resistor::getName()  //accessor
{
    return name;
}

double Resistor::getResistance() //accessor
{
    return resistance;
}

int Resistor::getFirstEndPoint() //accessor
{
    return endPoints[0];
}

int Resistor::getSecondEndPoint()//accessor
{
    return endPoints[1];
}

void Resistor::setResistance(double resistance_) //mutator
{
    resistance = resistance_;
}

Resistor* Resistor::getNext ()//accessor
{
    return next;
}

void Resistor::setNext(Resistor *ptr) //mutator
{
    next = ptr;
}
        