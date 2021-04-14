#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
using namespace std;
//The Window class
class Window{
    public:
        Window();
        ~Window();
        bool isOpen; // Variable for whether or not a student is at this window
        int timeIdle; // Variable keeping track of the amount of time a window is idle for
        int timeUntilOpen; // Variable keeping track of the time until the window is going to be open again
};
#endif