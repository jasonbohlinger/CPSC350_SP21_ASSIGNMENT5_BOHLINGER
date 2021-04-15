#include "Simulation.h"
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
#include <iostream>
#include <algorithm>
using namespace std;



Simulation::Simulation(){ // Default constructor initializes all member variables and sets the number of windows to 0
    this->studentLine = new GenQueue<Student*>;
    this->windows = new Window[0];
    this->numWindows = 0;
    this->pastStudents = new vector<Student>;
}

Simulation::Simulation(int numWindows){ // Overloaded constructor intiializes all member variables and sets the number of windows to numWindows
    this->studentLine = new GenQueue<Student*>;
    this->numWindows = numWindows;
    this->windows = new Window[this->numWindows];
    this->pastStudents = new vector<Student>;
}

Simulation::~Simulation(){
    delete studentLine;
    delete [] windows;
    delete pastStudents;
}


//Adds a new student to the end of the queue
void Simulation::addStudent(int timeNeeded, int currentClockTick){
    Student *thisStudent = new Student(timeNeeded, currentClockTick);
    studentLine->insert(thisStudent);
}

//If window(s) are available, sends student(s) to the available window(s). 
// currentClockTick represents the time that the student is leaving the line
void Simulation::sendStudentsToWindows(int currentClockTick){
   for(int i = 0; i < numWindows; ++i){
      if(windows[i].isOpen){
         if(studentLine->getSize() != 0){
            windows[i].isOpen = false;
            //Sets the window's time until open to the amount of time the student is spending at the window
            windows[i].timeUntilOpen = studentLine->peek()->timeNeeded;
            //Sets the student's time waited in line to the difference of the time they arrived and the time they are leaving the line
            studentLine->peek()->setTimeWaited(currentClockTick - studentLine->peek()->timeArrived);
            pastStudents->push_back(*(studentLine->peek())); // Adds the student (by value) to the end of the pastStudents vector
            studentLine->remove(); // Removes the student from the line
         }
      }
   }
}

//Increments the amount of time that a window has been idle for
void Simulation::incrementWindowIdleTime(int x){
   for(int i = 0; i < numWindows; ++i){
      if(windows[i].isOpen){
         windows[i].timeIdle = windows[i].timeIdle + x;
      }
   }
}

//Decrements the amount of time that a window has until it is open again
void Simulation::decrementWindowTimers(int x){
   for(int i = 0; i < numWindows; ++i){
      if(!windows[i].isOpen){
         windows[i].timeUntilOpen = windows[i].timeUntilOpen - x;
         if(windows[i].timeUntilOpen <= 0){
            windows[i].isOpen = true;
         }
      }
   }
}

int Simulation::getStudentLineSize(){
   return studentLine->getSize();
}

// Returns true if all of the windows in the window array are empty
bool Simulation::windowsAreEmpty(){
   for(int i = 0; i < numWindows; ++i){
      if(!windows[i].isOpen){
         return false;
      }
   }
   return true;
}

//Allows std::sort to sort the pastStudents vector
bool sortStudents(const Student& one, const Student& two){
   return (one.timeWaited < two.timeWaited);
}

//Calculates and gets statistics for the simulation: 
// 1. The mean student wait time.
// 2. The median student wait time. 
// 3. The longest student wait time. 
// 4. The number of students waiting over 10 minutes.
// 5. The mean window idle time.
// 6. The longest window idle time.
// 7. The number of windows idle for over 5 minutes.
void Simulation::getStats(){
   // 1. The mean student wait time
   float meanStudentWaitTime;
   int totalStudentWaitTime = 0;
   for(int i = 0; i < pastStudents->size(); ++i){
      totalStudentWaitTime += pastStudents->at(i).timeWaited;
   }
   meanStudentWaitTime = ((float)totalStudentWaitTime / (float)pastStudents->size());
   cout << "Mean student wait time: " << meanStudentWaitTime << endl;
   
   // 2. The median student wait time
   float medianStudentWaitTime = 0;
   std::sort(pastStudents->begin(), pastStudents->end(), sortStudents);
   if(pastStudents->size() % 2 != 0){
      Student middle = pastStudents->at(pastStudents->size() / 2);
      medianStudentWaitTime = middle.timeWaited;
   } else{
      Student middleLeft = pastStudents->at((pastStudents->size() / 2) - 1);
      Student middleRight = pastStudents->at(pastStudents->size() / 2);
      medianStudentWaitTime = (float)(middleLeft.timeWaited + middleRight.timeWaited) / 2.0;
   }
   cout << "Median student wait time: " << medianStudentWaitTime << endl;
   
   // 3. The longest student wait time
   float longestStudentWaitTime = pastStudents->at(pastStudents->size() - 1).timeWaited; // pastStudents is already sorted
   cout << "Longest student wait time: " << longestStudentWaitTime << endl;
   
   // 4. The number of students waiting over 10 minutes
   int numStudentsOverTen = 0;
   for(int i = 0; i < pastStudents->size(); ++i){
      if(pastStudents->at(i).timeWaited > 10){
         ++numStudentsOverTen;
      }
   }
   cout << "The number of students waiting over 10 minutes: " << numStudentsOverTen << endl;
   
   
   // 5. The mean window idle time
   float meanWindowIdleTime;
   int totalWindowIdleTime = 0;
   for(int i = 0; i < numWindows; ++i){
      totalWindowIdleTime += windows[i].timeIdle;
   }
   meanWindowIdleTime = (float)totalWindowIdleTime / (float)numWindows;
   cout << "The mean window idle time: " << meanWindowIdleTime << endl;
   
   // 6. The longest window idle time
   int longestWindowIdleTime = windows[0].timeIdle;
   for(int i = 0; i < numWindows; ++i){
      if(windows[i].timeIdle > longestWindowIdleTime){
         longestWindowIdleTime = windows[i].timeIdle;
      }
   }
   cout << "The longest window idle time: " << longestWindowIdleTime << endl;
   
   // 7. The number of windows idle for over 5 minutes
   int numWindowsOverFive = 0;
   for(int i = 0; i < numWindows; ++i){
      if(windows[i].timeIdle > 5){
         ++numWindowsOverFive;
      }
   }
   cout << "The number of windows idle for over 5 minutes: " << numWindowsOverFive << endl;
}

