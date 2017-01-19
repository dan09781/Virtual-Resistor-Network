/* 
 * File:   Node.h
 * Author: mindanie
 *
 * Created on October 12, 2015, 4:08 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>   
#include <sstream>
#include <iomanip>
#include <cctype>
#ifndef NODE_H
#define NODE_H
#include "ResistorList.h"

using namespace std;

class Node {
    private:
        int id; 
        int numRes; 
        double voltage;
        ResistorList *res;
        Node* next;
        bool setV;
        
    public:
    Node(int nodeID);
    Node(int nodeID, double v);
    ~Node();
    void setVoltage (double v);
    int getID ();
    Node* getNext ();
    void setNext (Node *n);
    ResistorList* getResList ();
    int getNumRes ();
    void incNumRes ();
    void setVSetTrue ();
    void setVSetFalse ();
    bool setVCheck ();
    void setNumRes (int n);
    void decNumRes();
    double getVoltage ();
};

#endif 
