#include "game.h"
// GLEW _MUST_ be included first
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  Get all GL prototypes
#define GL_GLEXT_PROTOTYPES
//  Select SDL, SDL2, GLFW or GLUT
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
#include <GL/glut.h>
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
int main(int argc, char** argv) {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s\n", SDL_GetError());
      return -1;
   }    
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_Window* window = SDL_CreateWindow("Final Project - Del Bene", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,900,900,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

   if (window == NULL) {
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL window: %s\n", SDL_GetError());
      SDL_Quit();
      return -1;
   }
   //if (!window) Fatal("Cannot create window\n");
   SDL_GL_CreateContext(window);
   SDL_GL_SetSwapInterval(1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glClearColor(0.0, 0.0, 0.0, 1.0);


   glutInit(&argc,argv);
   // glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

   Game* game = new Game(window);
   game->run();
   SDL_Quit();
   return 0;
}