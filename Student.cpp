#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(){ // Default constructor initializing all member variables to 0
    timeNeeded = 0;
    timeWaited = 0;
    this->timeArrived = 0;
}

Student::Student(int timeNeeded, int timeArrived){ // Overloaded constructor intializing timeNeeded and timeArrived to given values
    this->timeNeeded = timeNeeded;
    timeWaited = 0;
    this->timeArrived = timeArrived;
}
Student::~Student(){}

void Student::setTimeWaited(int x){
   this->timeWaited = x;
}
