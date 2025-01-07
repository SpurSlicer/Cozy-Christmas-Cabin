#ifndef CAMERA_H
#define CAMERA_H
#include "object.h"
#include <cmath>

typedef enum {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
} MovementState;

typedef struct {
    bool LEFT = false;
    bool RIGHT = false;
    bool UP = false;
    bool DOWN = false;
} MovementFlag;

class Camera : public Object {
    private: 
        bool is_paused = false;
        int th = 0;
        int ph = 0;
        double zh = 0; // ?
        double asp = 1;
        int fov = 85;
        double dim = 29.0;
        double pos_x = 12.5, pos_y = 4.0, pos_z = 5.0;
        MovementFlag movement;
    public:
        // Camera();
        void project();
        void resetAngles();
        void resetAnglesPerpendicular();
        void reshapeAsp(int, int);
        void rotate(int, int);
        void idleSetZh(double);
        int getTh();
        int getPh();
        void display();
        void move();
        bool checkColission(float, float, float);
        void toggleOn(MovementState);
        void toggleOff(MovementState);
        void togglePausedState();
};

#endif