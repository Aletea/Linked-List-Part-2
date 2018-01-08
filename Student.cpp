#include <iostream>
#include <cstring>
#include "Student.h"

using namespace std;

//set student variables
Student::Student(char* fN, char* lN, int Identify, double GP) {
  firstName = fN;
  lastName = lN;
  ID = Identify;
  GPA = GP;
}

//delete name pointers
Student::~Student() {
  delete firstName;
  delete lastName;
}

//combine the first and second names with a space in between, then return the full name
char* Student::getName() {
  char* fullName = new char[80];
  strcpy(fullName, firstName);
  fullName[strlen(fullName)] = ' ';
  int count = 0;
  for (int i = strlen(fullName); i < strlen(fullName) + strlen(lastName); i++) {
    fullName[i] = lastName[count];
    count++;
  }
  fullName[strlen(fullName)] = '\0';
  return fullName;
}

//getters for ID and GPA
int Student::getID() {
  return ID;
  
}

double Student::getGPA() {
  return GPA;
}
