#include "Window.h"
#include <iostream>
using namespace std;

Window::Window(){
    isOpen = true;
    timeIdle = 0;
    timeUntilOpen = 0;
}

Window::~Window(){}