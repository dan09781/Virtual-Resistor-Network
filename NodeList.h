/* 
 * File:   NodeList.h
 * Author: mindanie
 *
 * Created on November 4, 2015, 8:04 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>   
#include <sstream>
#include <iomanip>
#include <cctype>
#ifndef NODELIST_H
#define	NODELIST_H
#include "Node.h"
using namespace std;
class NodeList {
private:
    Node* head;
public:
    NodeList ();
    ~NodeList ();
    Node *findNode (int nodeID);
    bool deleteNode (int nodeID);
    bool insert (Node *ptr);
    Node *getHead ();
    Node *setHead (Node *ptr);
};


#endif	/* NODELIST_H */

