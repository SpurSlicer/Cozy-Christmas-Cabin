#ifndef MODEL_H
#define MODEL_H
#include "object.h"

class ArmChair : public Object {
    private:
    public: 
        ArmChair();
        void draw();
};

class Bookshelf : public Object {
    private:
    public: 
        Bookshelf();
        void draw();
};
#endif