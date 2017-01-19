/* 
 * File:   Resistor.h
 * Author: mindanie
 *
 * Created on October 12, 2015, 4:08 PM
 */

#ifndef RESISTOR_H
#define RESISTOR_H
#include <string>
#include <iostream>
#include <cstdlib>
#include <string>   
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

class Resistor {
    private:
        double resistance;
        Resistor* next;
        string name;
        int endPoints [2];
        
    public:
    Resistor(double res, string rName, int IDs[2]);
    ~Resistor();
    double getResistance ();
    void setResistance (double resistance_);
    string getName ();
    int getFirstEndPoint ();
    int getSecondEndPoint ();
    Resistor *getNext ();
    void setNext (Resistor* ptr);

};



#endif 
   