#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
using namespace std;
class Window{
    public:
        Window();
        ~Window();
        bool isOpen;
        int timeIdle;
        int timeUntilOpen;
};
#endif