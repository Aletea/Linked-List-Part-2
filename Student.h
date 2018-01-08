#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

using namespace std;

class Student {
 public:
  //constructore/destructor
  Student(char* firstName, char* lastName, int ID, double GPA);
  ~Student();
  //getters
  char* getName();
  int getID();
  double getGPA();

 private:
  char* firstName;
  char* lastName;
  int ID;
  double GPA;
};

#endif
