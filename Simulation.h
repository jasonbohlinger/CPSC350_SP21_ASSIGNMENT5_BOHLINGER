#ifndef SIMULATION_H
#define SIMULATION_H
#include <iostream>
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
#include <vector>

class Simulation{
    public:
        Simulation();
        Simulation(int numWindows);
        ~Simulation();

        void addStudent(int timeNeeded, int currentClockTick);
        void sendStudentsToWindows(int currentClockTick);
        void incrementWindowIdleTime(int x);
        void decrementWindowTimers(int x);
        int getStudentLineSize();
        bool windowsAreEmpty();
        void getStats();
        //bool sortStudents(const Student &one, const Student& two);
    private:
        GenQueue<Student*> *studentLine;
        Window *windows;
        vector<Student> *pastStudents;
        int numWindows;
};

#endif