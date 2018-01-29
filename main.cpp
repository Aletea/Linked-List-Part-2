#include <iostream>
#include <cstring>
#include "Node.h"
#include "Student.h"
#include <iomanip>

using namespace std;

//methods
Student* addStudent();
void addNode(Student* student, Node* &current, Node* &start);
void printNode(Node* start);
void deleteStudent(int studentID, Node* &start, Node* current);
Node* findNode(Node* newNode, Node* start);
double average(Node* start, double GPA, int count);

int main() {
  //beginnint node, most recently added node
  Node* start = NULL;
  Node* current = start;
  bool adding = true;
  //INFINATE LOOP, until exited when you quit
  while (adding == true) {
    //input demand
    char* input = new char[80];
    do {
      cout << "'add' 'quit' 'delete' 'average' or 'print'?" << endl;
      input = new char[80];
      cin.get(input, 80);
      cin.get();
    } while (strcmp(input, "average") != 0 && strcmp(input, "add") != 0 && strcmp(input, "print") != 0 && strcmp(input, "quit") != 0 && strcmp(input, "delete") != 0);
    //check for demand
    if (strcmp(input, "add") == 0) {
      //create a new student
      Student* newStudent = addStudent();
      //create a new Node with that Student
      addNode(newStudent, current, start);
    }
    //break the while loop if quiting
    else if (strcmp(input, "quit") == 0) {
      break;
    }
    else if(strcmp(input, "delete") == 0) {
      //input student name
      cout << "Student ID: ";
      int studentID;
      cin >> studentID;
      cin.ignore();
      //delete that Node and student
      deleteStudent(studentID, start, start);
    }
    else if (strcmp(input, "average") == 0) {
      //find average GPA and print to 2 decimal places
      if (start != NULL) {
	int begin = 0;
	double averageGPA = average(start, begin, begin);
	cout << "Average GPA: ";
	cout << fixed;
	cout << setprecision(2);
	cout << averageGPA << endl;
      }
      else {
	cout << "No Average" << endl;
      }
    }
    else {
      //print out linked list
      printNode(start);
    }
  }
  return 0;
}
//take input for name, ID, and GPA, then create a student with the following
Student* addStudent() {
  cout << "First Name: ";
  char* firstName = new char[40];
  cin.get(firstName, 40);
  cin.get();
  cout << "Last Name: ";
  char* lastName = new char[40];
  cin.get(lastName, 40);
  cin.get();
  cout << "ID: ";
  int ID;
  cin >> ID;
  cin.ignore();
  cout << "GPA: ";
  double GPA;
  cin >> GPA;
  cin.ignore();
  Student* newStudent = new Student(firstName, lastName, ID, GPA);
  return newStudent;
}


void addNode(Student* student, Node* &current, Node* &start) {
  //create a new node
  Node* newNode = new Node(student);
  
  //if there is no first Node, create first Node
  if (start == NULL) {
    start = newNode;
    current = start;
    return;
  }
  //find where to place the node
  Node* insertNode = findNode(newNode, start);
  //if it is null, there are no Nodes yet: set as 1st node
  if (insertNode == NULL) {
    newNode->setNext(start);
    start = newNode;
  }
  //if this node belongs on the end, simply set it there
  else if (insertNode->getNext() == NULL) {
    insertNode->setNext(newNode);
  }
  //if node needs to be inserted, set next for insertNode and newNode
  else {
    newNode->setNext(insertNode->getNext());
    insertNode->setNext(newNode);
  }
  //if on the end, its the current Node
  if (newNode->getNext() == NULL) {
    current = newNode;
  }
  
  /*//if this is the last node in the linked list, the new node is next
  //attach node to linked list
  if (current != NULL && current->getNext() == NULL) {
    current->setNext(newNode);
    //reset last Node
    current = newNode;
  
    return;
  }
  //if current is not the last node, run for the next node (shouldn't happen)
  if (current != NULL && current->getNext() != NULL) {
    current = current->getNext();
    addNode(student, current, start);
    }*/
}

//find where the ID fits in the sequence
Node* findNode(Node* newNode, Node* start) {
  //if goes after start, return start
  if (start->getNext() == NULL && start->getStudent()->getID() < newNode->getStudent()->getID()) {
    return start;
  }
  //if newNode is the smallest, return NULL
  else if (start->getNext() == NULL) {
    return NULL;
  }
  //if the next slot is where newNode should be inserted, return start
  else if (start->getNext()->getStudent()->getID() > newNode->getStudent()->getID() &&
	   start->getStudent()->getID() < newNode->getStudent()->getID()) {
    return start;
  }
  //otherwise, move on to next Node
  findNode(newNode, start->getNext());
}

void printNode(Node* start) {
  //start with first node and print
  if (start == NULL) {
    cout << "Nothing to print" << endl;
    return;
  }
  Node* current = start;
  Student* currentStudent = current->getStudent();
  cout << "Name: " << currentStudent->getName() << endl;
  cout << "ID: " << currentStudent->getID() << endl;
  cout << fixed;
  cout << setprecision(2);
  cout << "GPA: " << currentStudent->getGPA() << endl;
  cout << endl;
  //if this is the last Node- we're done!
  if (current->getNext() != NULL) {
    current = current->getNext();
    printNode(current);
  }
  return;
}


  


void deleteStudent(int studentID, Node* &start, Node* current) {
  if (start == NULL) {
    cout << "no students" << endl;
    return;
  }
  //if the first node is this one, delete the first node and reset the new first node
  if (current == start && current->getStudent()->getID() == studentID) {
    start = current->getNext();
    delete current;
    return;
  }
  //if we've already gone through all nodes, this student does not exist
  else if (current->getNext() == NULL) {
    cout << "Could not find student" << endl;
    return;
  }
  //if this is the node! reset this node next node, and delete its next node
  else if (current->getNext()->getStudent()->getID() == studentID) {
    Node* deleteNode = current->getNext();
    if (current->getNext()->getNext() == NULL) {
      current->setNext(NULL);
    }
    else {
      current->setNext(current->getNext()->getNext());
      delete deleteNode;
    }
    return;
  }
  //iterate to the next node if not found
  deleteStudent(studentID, start, current->getNext());
  
}
//find average GPA
double average (Node* start, double GPA, int count) {
  //accumulate GPAS
  GPA += start->getStudent()->getGPA();
  //how many GPAS
  count++;
  //add next GPA if there is one
  if (start->getNext() != NULL) {
    average(start->getNext(), GPA, count);
  }
  //otherwise use division to find GPA
  else {
    double finalGPA = GPA/count;
    return finalGPA;
  }
}
