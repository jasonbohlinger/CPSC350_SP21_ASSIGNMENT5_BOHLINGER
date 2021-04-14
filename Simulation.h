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
        Simulation(int numWindows); // Initizializes the simulation with numWindows amount of windows
        ~Simulation();

        void addStudent(int timeNeeded, int currentClockTick); // Adds a student to the end of the line (queue)
        void sendStudentsToWindows(int currentClockTick); // If windows are open, remove students from the queue
                                                            // and move them to the available window(s)
        void incrementWindowIdleTime(int x); // If a window is not occupied, increment that window's time idle
        void decrementWindowTimers(int x); // If a window is occupied, decrement the time left until that window is available again
        int getStudentLineSize(); // Get the number of students currently waiting in line
        bool windowsAreEmpty(); // Returns a boolean indicating whether the windows are all not occupied or not
        void getStats(); // Calculates and prints the necessary statistics
    private:
        GenQueue<Student*> *studentLine; // A queue of student pointers representing the line of students not at the windows
        Window *windows; // An array of windows representing the windows at the Registrar's office
        vector<Student> *pastStudents; // A vector of all students that have passed through the simulation necessary for statistics and calculations
        int numWindows; // The number of windows at the office
};

#endif