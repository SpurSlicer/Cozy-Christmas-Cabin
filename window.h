#ifndef WINDOW_H
#define WINDOW_H
#include "object.h"

class Window : public Object {
    private:
        bool state = false;
        void drawWindow();
        void drawWindowTop();
    public: 
        //House();
        void drawLeft();
        void drawRight();
        void toggleState();
};
#endif