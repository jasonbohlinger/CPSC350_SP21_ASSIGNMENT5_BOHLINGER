#include "Simulation.h"
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
#include <iostream>
#include <algorithm>
using namespace std;

Simulation::Simulation(){
    this->studentLine = new GenQueue<Student*>;
    this->windows = new Window[0];
    this->pastStudents = new vector<Student>;
}

Simulation::Simulation(int numWindows){
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

void Simulation::addStudent(int timeNeeded, int currentClockTick){
    Student *thisStudent = new Student(timeNeeded, currentClockTick);
    studentLine->insert(thisStudent);
}

void Simulation::sendStudentsToWindows(int currentClockTick){
   for(int i = 0; i < numWindows; ++i){
      if(windows[i].isOpen){
         if(studentLine->getSize() != 0){
            
            windows[i].isOpen = false;
            windows[i].timeUntilOpen = studentLine->peek()->timeNeeded;
            studentLine->peek()->setTimeWaited(currentClockTick - studentLine->peek()->timeArrived);
            pastStudents->push_back(*(studentLine->peek()));
            cout << "STUDENT WAIT TIME: " << pastStudents->at(pastStudents->size() - 1).timeWaited << endl;
            studentLine->remove();
         }
      }
   }
}

void Simulation::incrementWindowIdleTime(int x){ // Where x is the difference between the current clock tick and the prior clock tick
   for(int i = 0; i < numWindows; ++i){
      if(windows[i].isOpen){
         windows[i].timeIdle = windows[i].timeIdle + x;
      }
   }
}

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

bool Simulation::windowsAreEmpty(){
   for(int i = 0; i < numWindows; ++i){
      if(!windows[i].isOpen){
         return false;
      }
   }
   return true;
}

bool sortStudents(const Student& one, const Student& two){
   return (one.timeWaited < two.timeWaited);
}

void Simulation::getStats(){
   float meanStudentWaitTime;
   int totalStudentWaitTime = 0;
   for(int i = 0; i < pastStudents->size(); ++i){
      totalStudentWaitTime += pastStudents->at(i).timeWaited;
   }
   meanStudentWaitTime = ((float)totalStudentWaitTime / (float)pastStudents->size());
   cout << "Mean student wait time: " << meanStudentWaitTime << endl;
   
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
   cout << "PRINTING PAST STUDENTS: " << endl;
   for(int i = 0; i < pastStudents->size(); ++i){
      cout << pastStudents->at(i).timeWaited << " ";
   }
   cout << endl;
   
   float longestStudentWaitTime = pastStudents->at(pastStudents->size() - 1).timeWaited;
   cout << "Longest student wait time: " << longestStudentWaitTime << endl;
   
   int numStudentsOverTen = 0;
   for(int i = 0; i < pastStudents->size(); ++i){
      if(pastStudents->at(i).timeWaited > 10){
         ++numStudentsOverTen;
      }
   }
   cout << "The number of students waiting over 10 minutes: " << numStudentsOverTen << endl;
   
   
   float meanWindowIdleTime;
   int totalWindowIdleTime = 0;
   for(int i = 0; i < numWindows; ++i){
      totalWindowIdleTime += windows[i].timeIdle;
   }
   meanWindowIdleTime = (float)totalWindowIdleTime / (float)numWindows;
   cout << "The mean window idle time: " << meanWindowIdleTime << endl;
   
   
   
   
   int longestWindowIdleTime = windows[0].timeIdle;
   for(int i = 0; i < numWindows; ++i){
      if(windows[i].timeIdle > longestWindowIdleTime){
         longestWindowIdleTime = windows[i].timeIdle;
      }
   }
   cout << "The longest window idle time: " << longestWindowIdleTime << endl;
   
   int numWindowsOverFive = 0;
   for(int i = 0; i < numWindows; ++i){
      if(windows[i].timeIdle > 5){
         ++numWindowsOverFive;
      }
   }
   cout << "The number of windows idle for over 5 minutes: " << numWindowsOverFive << endl;
}