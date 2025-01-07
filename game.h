#ifndef GAME_H
#define GAME_H
#include "object.h"
#include "camera.h"
#include "house.h"
#include "window.h"
#include "tree.h"
#include "snow_generator.h"
#include "models.h"
//#include <libpng/png.h> (for textures eventually)
/*typedef struct shapes {
    house* house;
} shapes;*/
#define LEN 8192  //  Maximum length of text string

typedef struct {
    bool run;
    bool axes;
    bool lighting;
    bool textures;
} global_settings;

typedef struct {
    House* house;
    Window* left_window;
    Window* right_window;
    Tree* tree;
    SnowGenerator* snow_flakes[2];
} game_objects;

class Game : public Object {
    private:
        double t;
        bool lighting_toggle = true;
        //shapes* shapes;
        Camera* camera;
        lighting_settings* lighting;
        global_settings* settings;
        game_objects* objects;
        SDL_Window* window;
        // ---------
        void toggleLighting();
        void toggleTextures();
        void toggleAxes();
        // void generateBMPs();
        bool key();
        void keyUp();
        void mouseMove(int, int);
        // --helpers--
        void Print(const char*, ...);
        void ErrCheck(const char*);
        void Fatal(const char* , ...);
        void Reverse(void* x,const int n);
        // unsigned int LoadTexBMP(const char*);
    public:
        Game(SDL_Window*);
        void display();
        //void idle();
        void reshape();
        void run();
};

#endif