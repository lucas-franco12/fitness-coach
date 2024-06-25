#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Exercise.hpp"

using namespace std;
class PlanNode 
{
public:
    Exercise* info;
    class PlanNode *next;
    class PlanNode *prev;

    PlanNode(Exercise* exercise_node) 
    {
        info = exercise_node; 
        next = nullptr; 
        prev = nullptr;
    }
};

class PlanLL 
{
public:
    PlanLL(); 
    ~PlanLL();    
    void insert(Exercise*);
    std::string deleteNode(std::string id);
    bool isInList(std::string id) const;
    void printPlan() const;

private:
    PlanNode* ListHead;
    PlanNode* ListTail;
    std::string deleteFromHead();
    std::string deleteFromTail();

};

PlanLL::PlanLL(): ListHead(nullptr), ListTail(nullptr) {  }


PlanLL::~PlanLL() {
    // Loop through all the nodes 
    // Let temp point to the current ListHead, then move the ListHead to next node, and delete temp
    while (ListHead) {
            PlanNode* temp = ListHead;
            ListHead = ListHead->next;
            delete temp;
    }

}


void PlanLL::insert(Exercise* exercise) {
     // If LinkedList is empty, then add value to the head
    if (ListHead == nullptr) {
        ListHead = new PlanNode(exercise);
        ListTail = ListHead;
    } else {
        // Add value to the end of the LinkedList
        PlanNode* newNode = new PlanNode(exercise);
        ListTail->next = newNode;
        newNode->prev = ListTail;
        ListTail = newNode;
    }

}


std::string PlanLL::deleteFromHead() {
    // If LinkedList is not empty, then delete the head and return its info
    // set ListHead to the next node, and delete the previous ListHead
    std::string res;
    if(ListHead == nullptr) return "-1";
    else{
        PlanNode* temp = ListHead;
        ListHead = ListHead->next;
        res = temp->info->ID;
        delete temp;
    }
    if (ListHead == nullptr) ListTail = nullptr;
    return res;
  
} 


std::string PlanLL::deleteFromTail() {
    // If LinkedList is empty, return -1
    if (ListHead == nullptr) return "-1";
    std::string res;
    // If LinkedList has only one node, then delete the node and return its value
    if (ListHead->next == nullptr) {
        res = ListHead->info->ID;
        delete ListHead;
        ListHead = nullptr;
        ListTail = nullptr;
    } else {
        PlanNode* cur = ListTail;
        ListTail = ListTail->prev;
        ListTail->next = nullptr;
        res = cur->info->ID;
        delete cur;  
    }
    return res;
  
}  


std::string PlanLL::deleteNode(std::string id) {
    PlanNode* cur = ListHead;
    // Find the node with the value
    while (cur && cur->info->ID != id){
        cur = cur->next;
    }
    // If node is not found, return -1
    if (cur == nullptr) {return "-1";};
    std::string res;
    // If node wants to be deleted is the ListHead, then delete the ListHead
    if (cur==ListHead){
       res = PlanLL::deleteFromHead();
    // If node wants to be deleted is the last node, then delete the last node
    } else if (cur->next == nullptr) {
       res = PlanLL::deleteFromTail();
    } else{
        // If node wants to be deleted is in the middle of the LinkedList, then delete the node
        // Connect the node before and after the node to be deleted
        PlanNode* before = cur->prev;
        PlanNode* after = cur->next;
        before->next = after;
        after->prev = before;
        res = cur->info->ID;
        delete cur;
    }
    return res;

  
}

bool PlanLL::isInList(std::string id) const {
    PlanNode* cur = ListHead;
    while (cur){
        // If value is found, return true
        if (cur->info->ID == id) 
            return true;
        cur = cur->next;
    }
    // If none of the nodes matches the value, return false
    return false;
}

void PlanLL::printPlan() const {
    // If LinkedList is empty, print "Plan is empty"
    if (ListHead == nullptr) {
        cout << "Plan is empty." << endl;
    } else {
        // Loop through the LinkedList and print each node
        PlanNode* cur = ListHead;
        while (cur) {
            cur->info->printInfo();
            cur = cur->next;
        }
    }
}





