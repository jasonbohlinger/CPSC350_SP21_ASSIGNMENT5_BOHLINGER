#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
using namespace std;

//The Student class
class Student{
    public:
        Student();
        Student(int timeNeeded, int timeArrived);
        ~Student();
        void setTimeWaited(int x);
        int timeNeeded; // The student's time needed at a window (given by the input file)
        int timeWaited; // The student's time waited in line not at a window (calculated when the student leaves the line)
        int timeArrived; // The clock tick when the student arrives in the line (given by the input file)
};

#endif