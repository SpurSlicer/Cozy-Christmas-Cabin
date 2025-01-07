#ifndef TREE_H
#define TREE_H
#include "object.h"

class Tree : public Object {
    private:
        bool state = false;
        void drawTreeTrunk(double);
        void drawBranches(double);
        void drawStar();
        void drawTreeSkirt();
    public: 
        Tree();
        void draw();
};
#endif