/* 
 * File:   ResistorList.h
 * Author: mindanie
 *
 * Created on November 4, 2015, 8:03 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>   
#include <sstream>
#include <iomanip>
#include <cctype>
#ifndef RESISTORLIST_H
#define	RESISTORLIST_H
#include "Resistor.h"

using namespace std;

class ResistorList {
private:
    Resistor* head;
public:
    ResistorList ();
    ~ResistorList ();
    bool insertResistor (Resistor* ptr);
    Resistor* getHead ();
    Resistor* setHead (Resistor* ptr);
};






#endif	/* RESISTORLIST_H */

