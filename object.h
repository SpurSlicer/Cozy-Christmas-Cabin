#ifndef OBJECT_H
#define OBJECT_H
// GLEW _MUST_ be included first
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  Get all GL prototypes
#define GL_GLEXT_PROTOTYPES
//  Select SDL, SDL2, GLFW or GLUT
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#if defined(SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#elif defined(SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#elif defined(GLFW)
#include <GLFW/glfw3.h>
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//  Make sure GLU and GL are included
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif
#include <libpng/png.h>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <string>

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.14159265/180))
#define Sin(x) (sin((x)*3.14159265/180))
#define MAX_VERTICES 16
struct gl_texture_t
{
  GLsizei width;
  GLsizei height;

  GLenum format;
  GLint internalFormat;
  GLuint id;

  GLubyte *texels;
};
typedef struct {
    int emission;
    int ambient;
    int diffuse;
    int specular;
    float shininess;
    int local;
} lighting_settings;
typedef struct { double x; double y; double z; } coordinate;
// enum generic_lighting_state {
//     PLUS_X = 0,
//     MINUS_X = 1,
//     PLUS_Y = 2,
//     MINUS_Y = 3,
//     PLUS_Z = 4,
//     MINUS_Z = 5
// };
typedef struct {
    std::vector<coordinate*> vertices;
    std::vector<coordinate*> uvs;
    std::vector<coordinate*> normals;
    std::vector<coordinate*> indices;
    std::vector<int> batch;
    std::vector<std::pair<int, std::string>> texs;
} Model;
// typedef struct
// {
//    char* name;                 //  Material name
//    float Ka[4],Kd[4],Ks[4],Ns; //  Colors and shininess
//    float d;                    //  Transparency
//    int map;                    //  Texture
// } mtl_t;
class Object {
    protected:
        //textures* texs;
        // Light values
        lighting_settings lighting = {
            .emission = 0,
            .ambient = 10,
            .diffuse = 30,
            .specular = 0,
            .shininess = 0.0,
            .local = 0
        };
        int smooth    =   1;  // Smooth/Flat shading
        const float WHITE[4] = {1, 1, 1, 1};
        const float BLACK[4] = {0, 0, 0, 1};
        const float YELLOW[4]   = {1.0,1.0,0.0,1.0};
        const float EMISSION[4] = {0.0,0.0,(float)0.01*lighting.emission,1.0};
        float tick = 0.0;
        std::map<std::string, int> shaders; 
        std::map<std::string, int> textures; 
        std::map<std::string, Model*> models;
    public:
        coordinate* generateNormalByTriangle(coordinate*, coordinate*, coordinate*);
        coordinate* generateNormalByTriangleFLIP(coordinate*, coordinate*, coordinate*);
        coordinate* generateNormalBySquare(coordinate*, coordinate*, coordinate*, coordinate*);
        coordinate* generateNormalBySquareFLIP(coordinate*, coordinate*, coordinate*, coordinate*);
        // void getGenericNormal(generic_lighting_state);
        void generateShader(std::string, std::string, std::string);
        void generateShader(std::string, int);
        void enableShader(std::string);
        void enableShaderWTick(std::string);
        void disableShader();
        void setVec3(std::string, std::string, double, double, double);
        void PrintShaderLog(int, char*);
        void generateTexture(std::string, std::string);
        void generateTexture(std::string, int);
        void applyTexture(std::string);
        void applyTexture(std::string, int);
        void enableTextures();
        void disableTextures();
        // void enableMultiTextures();
        // void disableMultiTextures();
        void generateModel(std::string, std::string);
        Model* getModel(std::string);
        void applyTexForModel(std::string, int);
        void updateTick();
};
#endif
