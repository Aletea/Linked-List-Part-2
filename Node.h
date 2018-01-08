#ifndef NODE_H
#define NODE_H
//NODE.h class

#include <iostream>
#include "Student.h"

class Node {

 private:

  //student that is contained in the element
  Student* s;
  //The next element on the list
  Node* n;

  


  
 public:

  //thats the constructor

  Node(Student* v); //constructor

  
  //Destructor
   ~Node();


  Node* getNext(); //get next Node pointer


  Student* getStudent(); //get student pointer


  void setNext(Node* nextC); //set the next pointer to the corresponding node pointer

  
  
};



#endif
