/* 
 * File:   Rparser.h
 * Author: mindanie
 *
 * Created on October 7, 2015, 12:41 PM
 */

#ifndef RPARSER_H
#define	RPARSER_H



#define INSERT_COUNT 5
#define MODIFY_COUNT 3
#define PRINT_COUNT 2
#define DELETE_COUNT 2
#include <cstdlib>
#include <iostream>
#include <string>   
#include <sstream>
#include <iomanip>
#include <cctype>
#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "NodeList.h"

using namespace std;

/*
 * 
 */
int word_per_line (const string &);
void insertR (const string& line, NodeList *List, ResistorList *RList);
void modifyR (const string& line, NodeList *List, ResistorList *RList);
void printR (const string& line, NodeList *List, ResistorList *RList);
void printNode (const string& line, NodeList *List, ResistorList *RList);
void deleteR (const string& line, NodeList *List, ResistorList *RList);
void setV (const string& line, NodeList *List, ResistorList *RList);
void unsetV (const string& line, NodeList *List, ResistorList *RList);
void solve (const string& line, NodeList *List, ResistorList *RList);
int Rparser (void);

#endif