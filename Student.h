#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
using namespace std;

class Student{
    public:
        Student();
        Student(int timeNeeded, int timeArrived);
        ~Student();
        void setTimeWaited(int x);
        int timeNeeded;
        int timeWaited;
        int timeArrived;
};

#endif