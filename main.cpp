#include "Simulation.h"
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

bool operator<(const Student &one, const Student &two){
   return (one.timeWaited < two.timeWaited);
}

int main(int argc, char** argv){
   ifstream reader;
   string fileName = argv[1];
   reader.open(fileName);
   
   if(!reader.is_open()){
      throw runtime_error ("Unable to open file " + fileName + ".");
   }
   
   int numWindows;
   reader >> numWindows;
   cout << numWindows << " windows." << endl;
   Simulation *s = new Simulation(numWindows);
   
   int currentTick = 0;
   int nextTickGivenByFile;
   reader >> nextTickGivenByFile;
   while(!reader.fail()){
      cout << "Current clock tick: " << currentTick << endl;
      cout << "Next tick: " << nextTickGivenByFile << endl;
      s->incrementWindowIdleTime(1);
      if(currentTick == nextTickGivenByFile){
         int numStudentsArriving;
         reader >> numStudentsArriving;
         cout << "Number of students arriving: " << numStudentsArriving << endl;
         for(int i = 0; i < numStudentsArriving; ++i){
            int studentTimeNeeded;
            reader >> studentTimeNeeded;
            s->addStudent(studentTimeNeeded, currentTick);
            cout << "Student time needed: " << studentTimeNeeded << endl;
         }
         if(!reader.eof()){
            reader >> nextTickGivenByFile;
         }
      }
      s->decrementWindowTimers(1);
      s->sendStudentsToWindows(currentTick);
      ++currentTick;
   }
   
   while(!s->windowsAreEmpty()){
      cout << "Current clock tick FROM OUTSIDE LOOP:  " << currentTick << endl;
      s->incrementWindowIdleTime(1);
      s->decrementWindowTimers(1);
      s->sendStudentsToWindows(currentTick);
      ++currentTick;
   }
   
   if(!reader.eof()){
      throw runtime_error ("Unable to fully parse the file");
   }
   
   s->getStats();
   delete s;
   
   /*
   int priorClockTick = 0;
   int currentClockTick = 0;
   Simulation *s = new Simulation(numWindows);
   while(!reader.fail()){
      string check;
      reader >> check;
      if(check.size() == 0){
         continue;
      }
      currentClockTick = stoi(check);
      cout << "Current clock tick: " << currentClockTick << endl;
      s->incrementWindowIdleTime(currentClockTick - priorClockTick);
      int numStudentsArriving;
      reader >> numStudentsArriving;
      cout << "Number of students arriving: " << numStudentsArriving << endl;
      for(int i = 0; i < numStudentsArriving; ++i){
         int studentTimeNeeded;
         reader >> studentTimeNeeded;
         s->addStudent(studentTimeNeeded, currentClockTick);
         cout << "Student time needed: " << studentTimeNeeded << endl;
      }
      s->decrementWindowTimers(currentClockTick - priorClockTick);
      s->sendStudentsToWindows(currentClockTick);
      priorClockTick = currentClockTick;
      
   }
   if(!reader.eof()){
      throw runtime_error ("Unable to fully parse the file");
   }
   while(!s->windowsAreEmpty()){
      s->incrementWindowIdleTime(currentClockTick - priorClockTick);
      s->decrementWindowTimers(currentClockTick - priorClockTick);
      s->sendStudentsToWindows(currentClockTick);
      priorClockTick = currentClockTick;
      ++currentClockTick;
   }
   
   s->getStats();
   delete s;
   */
   /*vector<Student> v;
   int count = 1;
   for(int i = 4; i >= 0; --i){
      Student* thisStudent = new Student;
      v.push_back(*thisStudent);
      v.at(v.size() - 1).setTimeWaited(i);
   }
   for(int i = 0; i < 5; ++i){
      cout << v.at(i).timeWaited << " ";
   }
   cout << endl;
   
   sort(v.begin(), v.end());
   
   for(int i = 0; i < 5; ++i){
      cout << v.at(i).timeWaited << " ";
   }
   cout << endl;*/
}