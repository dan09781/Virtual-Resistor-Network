/* 
 * File:   parser.cpp
 * Author: mindanie
 *
 * Created on September 22, 2015, 10:30 AM
 */
#include "Rparser.h"

using namespace std;

/*
 * 
 */
int Rparser(){
    NodeList *newList = new NodeList ();   //node list
    ResistorList *newRList = new ResistorList ();  //general resistor list
    string line, command;
    int wordcount;
    
    cout << "> ";
    getline (cin, line);    //read line from the user
    while (!cin.eof()){
        wordcount = word_per_line (line);
        stringstream linestream (line);
        linestream >> command;
        if  (wordcount == 0 && linestream.eof())
            cout << "Error: invalid command" << endl; //when nothing is entered as command, output error
        else if(command == "setV") //when setV is entered as command , call setV function
            setV (line, newList, newRList);
        else if(command == "unsetV") //when unsetV is entered as command , call unsetV function
            unsetV (line, newList, newRList);
        else if(command == "insertR") //when insertR is entered as command , call insertR function
            insertR (line, newList, newRList);
        else if (command == "modifyR") //when modifyR is entered as command , call modifyR function
            modifyR (line, newList, newRList);
        else if (command == "printR") //when printR is entered as command , call printR function
            printR (line, newList, newRList);        
        else if (command == "deleteR") //when deleteR is entered as command , call deleteR function
            deleteR (line, newList, newRList);
        else if (command == "printNode") //when printNode is entered as command , call printNode function
            printNode (line, newList, newRList);
        else if (command == "solve") //when solve is entered as command , call solve function
            solve (line, newList, newRList);
        else
            cout << "Error: invalid command" << endl; //when anything else is entered, output error
        cout << "> ";
        getline (cin, line);
    }
    delete newRList;
    delete newList;   
    return 0;
}   

void insertR (const string& line, NodeList *List, ResistorList *RList){
                double res; 
                bool resExist = false;
                bool node1Exist = false, node2Exist = false;
                int IDs [2];
                string rName, command;
                stringstream linestream(line);
                linestream >>command >> rName >> res >> IDs[0] >> IDs[1]; 
                Resistor *tRes = RList->getHead();
                while (tRes!=NULL)  //check if resistor name already exists
                {
                    if (tRes->getName() == rName){
                        resExist = true;
                        cout << "Error: " << "resistor " << rName << " already exists" << endl;
                    }
                    tRes = tRes->getNext();   
                }
                if (resExist == false)  
                {
                    Resistor *newRes = new Resistor(res, rName, IDs);  //create new resistor to insert into the general resistor list
                    RList->insertResistor(newRes);
                    if (IDs [0]==IDs [1])
                        cout << "Error: both terminals of resistor connect to node " << IDs[0] << endl;
                    Node *tptr=List->getHead();
                    while (tptr!=NULL){         //check if nodes already exist
                        if (tptr->getID()==IDs[0])
                            node1Exist=true;
                        tptr=tptr->getNext();
                    }
                    Node* tptr2=List->getHead();
                    while (tptr2!=NULL){     
                        if (tptr2->getID()==IDs[1])
                            node2Exist=true;
                        tptr2=tptr2->getNext();
                    }
                    if (node1Exist==false&&node2Exist==false)  //according to existence of entered nodes, insert node into the node list
                    {
                        Node *newNode = new Node(IDs[0]);
                        List->insert(newNode);
                        Node *newNode1 = new Node(IDs[1]);
                        List->insert(newNode1);
                    }
                    if (node1Exist==false&&node2Exist==true)
                    {
                        Node *newNode = new Node(IDs[0]);
                        List->insert(newNode);
                    }
                    if (node1Exist==true&&node2Exist==false)
                    {
                        Node *newNode1 = new Node(IDs[1]);
                        List->insert(newNode1);
                    }
                    Node *tptr3 = List->getHead();
                    Resistor *newRes1 = new Resistor(res, rName, IDs);      //insert resistors into the resistor lists in the nodes
                    Resistor *newRes2 = new Resistor(res, rName, IDs);
                    while (tptr3!=NULL)
                    {
                        if (tptr3->getID()==IDs[0])
                        {
                            tptr3->getResList()->insertResistor(newRes1);
                            tptr3->incNumRes();
                        }
                        else if (tptr3->getID()==IDs[1])
                        {
                            tptr3->getResList()->insertResistor(newRes2);
                            tptr3->incNumRes();
                        }
                        tptr3=tptr3->getNext();
                    }
                    cout << "Inserted: resistor " << rName << " " << fixed  << setprecision(2) << res
                            << " Ohms " << IDs[0] << " -> " << IDs[1] << endl; 
                }
}

void printNode (const string& line, NodeList *List, ResistorList *RList){
    stringstream linestream (line);
    stringstream linestream2 (line);  //stringstreams that will be used to read error check inputs
    string command, commandDummy;   //variables to read the command
    int nodeID, node1, node2, numRes, targetNode; 
    string rName, node1Check;
    double res;
    linestream >> command >> nodeID;
    linestream2 >> commandDummy >> node1Check; //read inputs into stringstreams
    cout << "Print:" << endl;
    if (node1Check == "all")
    {
        Node* tptr = List->getHead();
        while (tptr!=NULL)      //print information about all the nodes existing in the node list
        {
            if (tptr->getNumRes()!=0)
            {
            targetNode=tptr->getID();
            numRes=tptr->getNumRes();
            cout << "Connections at node " << targetNode << ": " << numRes << " resistor(s)" << endl;
            Resistor *tRes = tptr->getResList()->getHead();
            while (tRes!=NULL)
            {
                node1=tRes->getFirstEndPoint();
                node2=tRes->getSecondEndPoint();
                res=tRes->getResistance();
                rName=tRes->getName();
                cout << "  " << rName << " " << fixed << setprecision(2) << res << " Ohms " << node1 << " -> " << node2 << endl;
                tRes=tRes->getNext();
            }
            }
            else if (tptr->getNumRes()==0 && tptr->setVCheck()==true)
                cout << "Connections at node " << tptr->getID() << ": " << fixed << setprecision(2) << tptr->getVoltage() << " V" << endl;
            tptr=tptr->getNext();
        }
    }
    else
    {
        Node* tptr2 = List->getHead();
        while (tptr2!=NULL)     //print information about the selected node existing in the node list
        {
            if (tptr2->getID()==nodeID && tptr2->getNumRes()!=0)
            {
                numRes=tptr2->getNumRes();
                cout << "Connections at node " << nodeID << ": " << numRes << " resistor(s)" << endl;
                Resistor* tRes2=tptr2->getResList()->getHead();
                while (tRes2!=NULL)
                {
                    node1=tRes2->getFirstEndPoint();
                    node2=tRes2->getSecondEndPoint();
                    res=tRes2->getResistance();
                    rName=tRes2->getName();
                    cout << "  " << rName << " " << fixed << setprecision(2) << res << " Ohms " << node1 << " -> " << node2 << endl;
                    tRes2=tRes2->getNext();
                }
            }
            if (tptr2->getNumRes()==0 && tptr2->setVCheck()==true)
                cout << "Connections at node " << tptr2->getID() << ": " << fixed << setprecision(2) << tptr2->getVoltage() << " V" << endl;
            tptr2=tptr2->getNext();
        }
    }
}




void deleteR (const string& line, NodeList *List, ResistorList *RList)
{
    stringstream linestream (line);     //stringstream to read the inputs
    string command, rName;
    linestream >> command >> rName;
    if (rName == "all")
    {
        Resistor *current=RList->getHead();     
        while (current!=NULL)       //delete all resistors in the general resistor list
        {
            Resistor *tptr=current;
            current=current->getNext();
            delete tptr;
        }
        Node *tptr1=List->getHead();
        while (tptr1!=NULL)     //delete all resistors in the node resistor list
        {
            Resistor *current1 = tptr1->getResList()->getHead();
            while (current1!=NULL)
            {
                Resistor *tptr2=current1;
                current1=current1->getNext();
                delete tptr2;
            }
            tptr1->setNumRes(0);
            tptr1=tptr1->getNext();
        }
        cout << "Deleted: all resistors" << endl;
    }
    else
    {
        Resistor *current=RList->getHead();
        Resistor *previous=NULL;
        bool resExist = false;
        while (current!=NULL && current->getName()!=rName)  //find the resistor that needs to be deleted
        {
            previous=current;
            current=current->getNext();
        }
        if (current!=NULL)
            resExist=true;
        if(previous==NULL&&resExist==true)      //delete the resistor from the general resistor list
        {
            RList->setHead(current->getNext());
            delete current;
        }
        else if (previous!=NULL&&resExist==true)
        {
            previous->setNext(current->getNext());
            delete current;
        }
        if (resExist==false)        //if resistor does not exist, output error
            cout << "Error: resistor " << rName << " not found" << endl; 
        Node *tptr=List->getHead();
        while (tptr!=NULL && resExist==true) //look for the resistor in each node resistor list
        {
            bool resExist1=false;
            Resistor *current1 = tptr->getResList()->getHead();
            Resistor *previous1 = NULL;
            while (current1!=NULL && current1->getName()!=rName)
            {
                previous1=current1;
                current1=current1->getNext();
            }
            if (current1!=NULL&&current1->getName() == rName)
                resExist1=true;
            if(previous1==NULL && resExist1==true)  //if resistor is found, delete it
            {
                tptr->getResList()->setHead(current1->getNext());
                delete current1;
                tptr->decNumRes();
            }
            else if (previous1!=NULL&&resExist1==true)
            {
                previous1->setNext(current1->getNext());
                delete current1;
                tptr->decNumRes();
            }
            tptr=tptr->getNext();
        }
        if (resExist==true)
            cout << "Deleted: resistor " << rName << endl;
    }
}
void modifyR (const string& line, NodeList *List, ResistorList *RList)
{
    stringstream linestream (line);     //stringstream to read inputs
    string command, rName;
    bool resExist = false;
    double modifiedRes, res;     //declare variables to be read and put into stringstream
    linestream >> command >> rName >> modifiedRes;
    Resistor* tRes = RList->getHead();
    while (tRes!=NULL)      //save the old resistance and modify the resistance to input value in the general resistor list
    {
        if (tRes->getName() == rName){
            res=tRes->getResistance();
            tRes->setResistance(modifiedRes);
            resExist = true;
        }
        tRes = tRes->getNext();   
    }
    Node* tptr = List->getHead();
    while (tptr!=NULL)
    {
        Resistor *tRes2 = tptr->getResList()->getHead();
        while (tRes2!=NULL)    //save the old resistance and modify the resistance to input value in the node resistor list
        {
            if (tRes2->getName()==rName)
            {
                tRes2->setResistance(modifiedRes);
                resExist = true;
            }
            tRes2=tRes2->getNext();
        }
        tptr=tptr->getNext();
    }
    if (resExist == true)
        cout << "Modified: resistor " << rName << " from " << fixed << setprecision(2) << res << " Ohms to " << modifiedRes << " Ohms" << endl;
    else if (resExist == false)
        cout << "Error: resistor " << rName << " not found" << endl;
}


void printR (const string& line, NodeList *List, ResistorList *RList)
{
    stringstream linestream (line);     //stringstream to read the inputs
    string command, rName;
    bool resExist=false;
    int node1, node2;
    double res;
    linestream >> command >> rName;
    Resistor* tRes = RList->getHead();
    while (tRes!=NULL)    //find resistor in the general resistor list and print its information
    {
        if (tRes->getName() == rName){
            resExist = true;
            node1 = tRes->getFirstEndPoint();
            node2 = tRes->getSecondEndPoint();
            res = tRes->getResistance();
        }
        tRes = tRes->getNext();   
    }
    if (resExist == true){
        cout << "Print:" << endl;
        cout << rName << " " << setw(20) << fixed << setprecision(2) << res << " Ohms " << node1 << " -> " << node2 << endl;
    }
    else if (resExist == false)
        cout << "Error: resistor " << rName << " not found" << endl;
}

void unsetV (const string& line, NodeList *List, ResistorList *RList)
{
    string command;
    int nodeID;
    stringstream linestream (line);
    linestream >> command >> nodeID;
    Node *tptr = List->getHead();
    while (tptr!=NULL)      //unset any set voltages
    {
        if (tptr->getID()==nodeID)
        {
            tptr->setVSetFalse();
            tptr->setVoltage(0);
        }
        tptr=tptr->getNext();
    }
    cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
}

void setV (const string& line, NodeList *List, ResistorList *RList)
{
    string command;
    int nodeID;
    double voltage;
    bool nodeExist = false;
    stringstream linestream (line);
    linestream >> command >> nodeID >> voltage;
    Node* tptr=List->getHead();
    while (tptr!=NULL)      //set voltage for existing node
    {
        if (tptr->getID()==nodeID)
        {
            nodeExist = true;
            tptr->setVoltage(voltage);
            tptr->setVSetTrue();
            cout << "Set: node " << nodeID << " to " << voltage << " Volts" << endl;  
        }
        tptr=tptr->getNext();
    }
    if (nodeExist == false)
    {
        Node *newNode = new Node(nodeID, voltage);      //if node does not exist, create a new one and set its voltage
        List->insert(newNode);
        cout << "Set: node " << nodeID << " to " << fixed << setprecision(2) << voltage << " Volts" << endl; 
    }
}

void solve (const string& line, NodeList *List, ResistorList *RList)
{
    Node *tptr=List->getHead();
    bool setCheck=false;
    while (tptr!=NULL)
    {
        if (tptr->setVCheck()==true)
            setCheck=true;
        tptr=tptr->getNext();
    }
    if (setCheck==false)
        cout << "Error: no nodes have their voltage set" << endl;     
}


int word_per_line (const string& line)
{
    int count = 0; //variable to count number of words
    stringstream s(line);   //stringstream to read the entire line
    string dummy;
    while (s >> dummy)  //as each word goes into dummy, increase number of words by 1
        count ++;
    return count; 
}


