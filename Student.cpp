#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(){
    timeNeeded = 0;
    timeWaited = 0;
}

Student::Student(int timeNeeded, int timeArrived){
    this->timeNeeded = timeNeeded;
    timeWaited = 0;
    this->timeArrived = timeArrived;
}

void Student::setTimeWaited(int x){
   this->timeWaited = x;
}
Student::~Student(){}
