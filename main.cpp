#include "Simulation.h"
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char** argv){
   ifstream reader;
   Simulation *s;
   try{
      string fileName = argv[1];
      //Opens a file for reading given the filename from a command line argument
      reader.open(fileName);
      
      if(!reader.is_open()){
         throw runtime_error ("Unable to open file " + fileName + ".");
      }
      
      //Creates a new simulation with the correct number of windows
      int numWindows;
      reader >> numWindows;
      s = new Simulation(numWindows);
      
      int currentTick = 0;
      //nextTickGivenByFile is the next clock tick that is in the input file
      int nextTickGivenByFile;
      reader >> nextTickGivenByFile;
      while(!reader.eof()){
         if(currentTick != 0){
            s->incrementWindowIdleTime(1); // Increment window idle time by 1
         }
         if(currentTick == nextTickGivenByFile){ // Students are arriving at this time if the time is given by the file
            int numStudentsArriving;
            reader >> numStudentsArriving;
            for(int i = 0; i < numStudentsArriving; ++i){
               int studentTimeNeeded;
               reader >> studentTimeNeeded;
               s->addStudent(studentTimeNeeded, currentTick); // Adds a student to the end of the line 
            }
            if(!reader.eof()){ // If this is not the end of the file, read the next time given by the file 
               reader >> nextTickGivenByFile;
            }
         }
         s->decrementWindowTimers(1); // Decrement the time until a window is open by 1
         s->sendStudentsToWindows(currentTick); // Send students from the line to any available windows
         ++currentTick; // Increment the current clock tick
      }
      while(!s->windowsAreEmpty()){
         s->incrementWindowIdleTime(1);
         s->decrementWindowTimers(1);
         s->sendStudentsToWindows(currentTick);
         ++currentTick;
      }
      s->getStats(); // Get the statistics from the simulation
      delete s; // Garbage collection
      reader.close();
   } catch(runtime_error e){
      cout << "Error: " << e.what() << endl;
      delete s;
   }
}