#ifndef SNOW_GENERATOR_H
#define SNOW_GENERATOR_H
#include "object.h"
#include <vector>

class SnowFlake : public Object {
    private: 
        double x;
        double y;
        double z;
        double y_vel;
        int tex_index;
        const std::string rem_white_name = "rem_white";
    public:
        SnowFlake(int, int);
        ~SnowFlake();
        bool deletable();
        void draw(bool);
};

class SnowGenerator : public Object {
    private:
        std::vector<SnowFlake*> snowflakes;
        const std::string rem_white_name = "rem_white";
    public: 
        SnowGenerator();
        void createSnowFlake();
        void drawLeft();
        void drawRight();
};
#endif