#ifndef HOUSE_H
#define HOUSE_H
#include "object.h"
#include "models.h"

#define LENGTH 25.0
#define WIDTH 25.0

class House : public Object {
    private:
        ArmChair* arm_chair;
        Bookshelf* bookshelf;
        bool is_extinguished;
        void drawCylinder(double);
        void drawDoorFrame();
        void drawWindowSills();
        void drawWindowWalls();
        void drawDoorWall();
        void drawFirePlaceWall();
        void drawMantle();
        void drawTV();
        void drawHearth();
        void drawInsideOfFireplace();
        void drawFirePlace();
        void drawFloor();
        void drawRoof();
        void drawFire();
        void drawRug();
        void drawSky();
        void drawStockings();
        void drawPictureFrames();
    public: 
        House();
        void draw();
        void toggleExtinguishState();
};
#endif