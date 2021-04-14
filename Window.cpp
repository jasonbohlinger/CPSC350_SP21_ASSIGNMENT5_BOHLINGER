#include "Window.h"
#include <iostream>
using namespace std;

Window::Window(){ // Default constructor intializing all member variables to 0
    isOpen = true;
    timeIdle = 0;
    timeUntilOpen = 0;
}

Window::~Window(){}