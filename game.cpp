#include "game.h"
#include <GL/glut.h>

Game::Game(SDL_Window* window) {
    this->window = window;
    this->t = 0.0;
    this->camera = new Camera();
    this->objects = new game_objects;
    this->objects->house = new House();
    this->objects->left_window = new Window();
    this->objects->right_window = new Window();
    this->objects->tree = new Tree();
    this->objects->snow_flakes[0] = new SnowGenerator();
    this->objects->snow_flakes[1] = new SnowGenerator();

    this->lighting = new lighting_settings;
    this->lighting->emission = 0;
    this->lighting->ambient = 40;
    this->lighting->diffuse = 80;
    this->lighting->specular = 10;
    this->lighting->shininess = 16;
    this->lighting->local = 0;

    this->settings = new global_settings;
    this->settings->run = true;
    this->settings->axes = true;
    this->settings->lighting = true;
    this->settings->textures = false;
}

void Game::toggleLighting() {
    
    //  Translate intensity to color 
    float Ambient[]   = {(float)0.01*this->lighting->ambient ,(float)0.01*this->lighting->ambient ,(float)0.01*this->lighting->ambient ,1.0};
    float Diffuse[]   = {(float)0.01*this->lighting->diffuse ,(float)0.01*this->lighting->diffuse ,(float)0.01*this->lighting->diffuse ,1.0};
    float Specular1[]  = {(float)0.01*this->lighting->specular,(float)0.01*this->lighting->specular,(float)0.01*this->lighting->specular,1.0};
    // const float Shininess[] = {(float)this->lighting->shininess};
    // float Emission[] = {0.0,0.0,0.0,1.0};
    //  Light position
    float Position1[]  = {12.5, 1.75, 26.0, 1.0};
    // float Position2[]  = {20.0, 9.5, 6.0, 1.0};

    // float shininess[] = {2};
    // glPushMatrix();
    // glTranslated(Position[0], Position[1], Position[2]);
    // glutSolidSphere(1.0, 25, 25);
    // glPopMatrix();
    // float Position[]  = {20.5, 1.0, 5.5, 1.0};
    // if (!this->lighting_toggle) {
    //     Ambient[3] = 0.0;
    //     Diffuse[3] = 0.0;
    //     Specular[3] = 0.0;
    //     Emission[3] = 0.0;
    // }
    //  Draw light position as ball (still no lighting here)
    //  OpenGL should normalize normal vectors
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,this->BLACK);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    if (this->lighting_toggle) {
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular1);
        glLightfv(GL_LIGHT0,GL_POSITION,Position1);
    } else {
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE , this->BLACK);
        glLightfv(GL_LIGHT0,GL_SPECULAR,this->BLACK);
        glLightfv(GL_LIGHT0,GL_POSITION,Position1);
    }    
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, this->WHITE);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, this->WHITE);
    // glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    // glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    // glMaterialfv(GL_FRONT,GL_SPECULAR,this->YELLOW);
    // glMaterialf(GL_FRONT,GL_SHININESS,this->lighting->shininess);

    // glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION ,1.0);
    // glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION   ,0.0);
    // glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.0);
    // glLightfv(GL_LIGHT0,GL_POSITION,Position); 
    // glLightfv(GL_LIGHT0,GL_AMBIENT ,this->BLACK);
    // glLightfv(GL_LIGHT0,GL_DIFFUSE ,this->WHITE);
    // glLightfv(GL_LIGHT0,GL_SPECULAR,this->BLACK);
    // glLightfv(GL_LIGHT0,GL_POSITION,Position);         
    // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,32);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
}

void Game::toggleTextures() {
    if (this->settings->textures) {
        glEnable(GL_TEXTURE_2D);
    } else {
        glDisable(GL_TEXTURE_2D);
    }
}
void Game::toggleAxes() {
    if (this->settings->axes) {
        const double len=20.0;  //  Length of axes
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(len,0.0,0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(0.0,len,0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(0.0,0.0,len);
        glEnd();
        //  Label axes
    }
}
// void Game::generateBMPs() { return; }
bool Game::key() { 
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    //int shift = SDL_GetModState()&KMOD_SHIFT;
    if (keys[SDL_SCANCODE_ESCAPE]) return false;
    else if (keys[SDL_SCANCODE_0]) this->camera->resetAngles();
    else if (keys[SDL_SCANCODE_9]) this->camera->resetAnglesPerpendicular();
    else if (keys[SDL_SCANCODE_PERIOD]) this->objects->left_window->toggleState();
    else if (keys[SDL_SCANCODE_COMMA]) this->objects->right_window->toggleState();
    else if (keys[SDL_SCANCODE_M]) {
        this->objects->house->toggleExtinguishState();
        this->lighting_toggle = !this->lighting_toggle;
    } else if (keys[SDL_SCANCODE_SPACE]) this->camera->togglePausedState();
    if (keys[SDL_SCANCODE_W]) {
        this->camera->toggleOn(UP);
    } 
    if (keys[SDL_SCANCODE_A]) {
        this->camera->toggleOn(LEFT);
    }
    if (keys[SDL_SCANCODE_S]) {
        this->camera->toggleOn(DOWN);
    }
    if (keys[SDL_SCANCODE_D]) {
        this->camera->toggleOn(RIGHT);
    }
    this->camera->project();
    return true;
}
void Game::keyUp() {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (!keys[SDL_SCANCODE_W]) {
        this->camera->toggleOff(UP);
    } 
    if (!keys[SDL_SCANCODE_A]) {
        this->camera->toggleOff(LEFT);
    }
    if (!keys[SDL_SCANCODE_S]) {
        this->camera->toggleOff(DOWN);
    }
    if (!keys[SDL_SCANCODE_D]) {
        this->camera->toggleOff(RIGHT);
    }
    this->camera->project();
}
void Game::mouseMove(int x, int y) {
    this->camera->rotate(x, y);
    this->camera->project();
}

void enableFog() {
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    float color[3] = {0.0, 0.0, 0.0};
    glFogfv(GL_FOG_COLOR, color);
    glFogf(GL_FOG_DENSITY, 0.005);
}

void disableFog() {
    glDisable(GL_FOG);
}


void Game::display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // erase window and depth buffers
    glLoadIdentity();
    this->camera->display(); // set viewport
    this->toggleLighting();
    this->toggleTextures();
    enableFog();
    this->objects->house->draw();
    this->objects->left_window->drawLeft();
    this->objects->right_window->drawRight();
    this->objects->tree->draw();
    this->objects->snow_flakes[0]->drawLeft();
    this->objects->snow_flakes[0]->drawRight();
    //this->toggleAxes();
    glDisable(GL_LIGHTING);
    ErrCheck("display");
    glFlush();
    SDL_GL_SwapWindow(this->window);
}
//void Game::idle() { }
void Game::reshape() {
    int width, height;
    SDL_GetWindowSize(this->window, &width, &height);
    this->camera->reshapeAsp(width, height);
    glViewport(0, 0, width, height);
    this->camera->project();
}
void Game::run() {
    printf("Running!\n");
    reshape();
    /*
    //  Initialize audio
    if (Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096)) Fatal("Cannot initialize audio\n");
    //  Load "The Wall"
    Mix_Music* music = Mix_LoadMUS("thewall.ogg");
    if (!music) Fatal("Cannot load thewall.ogg\n");
    //  Load boing
    Mix_Chunk* boing = Mix_LoadWAV("boing.wav");
    if (!boing) Fatal("Cannot load boing.wav\n");
    //  Play (looping)
    Mix_PlayMusic(music,-1);
    */
    //  SDL event loop
    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096)) {
        printf("[ERROR] canot initialize audio\n");
    }
    Mix_Music* music = Mix_LoadMUS("_jingle_bell_rock.ogg");
    if (!music) {
        printf("[ERROR] could not play music! Proceeding anyways...\n");
    } else {
        Mix_PlayMusic(music, -1);
    }
    ErrCheck("init");
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST); // enable Z-buffering
    glEnable(GL_BLEND); // enable alpha color channel
    // glShadeModel(GL_SMOOTH);
    // glShadeModel(GL_FLAT);
    this->camera->rotate(180, 0);
    while (this->settings->run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_WINDOWEVENT)  {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_SetWindowSize(this->window, event.window.data1, event.window.data2);
                    reshape();
                }
            } if (event.type == SDL_KEYDOWN) {
                this->settings->run = this->key();
            } if (event.type == SDL_KEYUP) {
                this->keyUp();
            } if (event.type == SDL_MOUSEMOTION) {
                this->mouseMove(event.motion.xrel, event.motion.yrel);
            } if (event.type == SDL_QUIT) {
                this->settings->run = false;
            }
        }
        /*const double temp_t = this->t + 0.5;
        if (this->t - temp > ) {
            this->settings->run = this->key();
        }*/
        //this->th = fmod(90*t, 360.0);
        this->display();
        this->camera->move();
        SDL_Delay(5);  //slow framerate to 100fps;
    }
    Mix_CloseAudio();
    SDL_Quit();
}

// -----------------------------
// -----------------------------
// ---------HELPERS-------------
// -----------------------------
// -----------------------------

/*void Game::Print(const char* format, ...) {
    char    buf[LEN];
    char*   ch=buf;
    va_list args;
    //  Turn the parameters into a character string
    va_start(args,format);
    vsnprintf(buf,LEN,format,args);
    va_end(args);
    //  Display the characters one at a time at the current raster position
    while (*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}*/

void Game::ErrCheck(const char* where) {
    int err = glGetError();
    if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

void Game::Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

void Game::Reverse(void* x,const int n)
{
   char* ch = (char*)x;
   for (int k=0;k<n/2;k++)
   {
      char tmp = ch[k];
      ch[k] = ch[n-1-k];
      ch[n-1-k] = tmp;
   }
}

// unsigned int Game::LoadTexBMP(const char* file)
// {
//    //  Open file
//    FILE* f = fopen(file,"rb");
//    if (!f) Fatal("Cannot open file %s\n",file);
//    //  Check image magic
//    unsigned short magic;
//    if (fread(&magic,2,1,f)!=1) Fatal("Cannot read magic from %s\n",file);
//    if (magic!=0x4D42 && magic!=0x424D) Fatal("Image magic not BMP in %s\n",file);
//    //  Read header
//    unsigned int dx,dy,off,k; // Image dimensions, offset and compression
//    unsigned short nbp,bpp;   // Planes and bits per pixel
//    if (fseek(f,8,SEEK_CUR) || fread(&off,4,1,f)!=1 ||
//        fseek(f,4,SEEK_CUR) || fread(&dx,4,1,f)!=1 || fread(&dy,4,1,f)!=1 ||
//        fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
//      Fatal("Cannot read header from %s\n",file);
//    //  Reverse bytes on big endian hardware (detected by backwards magic)
//    if (magic==0x424D)
//    {
//       Reverse(&off,4);
//       Reverse(&dx,4);
//       Reverse(&dy,4);
//       Reverse(&nbp,2);
//       Reverse(&bpp,2);
//       Reverse(&k,4);
//    }
//    //  Check image parameters
//    unsigned int max;
//    glGetIntegerv(GL_MAX_TEXTURE_SIZE,(int*)&max);
//    if (dx<1 || dx>max) Fatal("%s image width %d out of range 1-%d\n",file,dx,max);
//    if (dy<1 || dy>max) Fatal("%s image height %d out of range 1-%d\n",file,dy,max);
//    if (nbp!=1)  Fatal("%s bit planes is not 1: %d\n",file,nbp);
//    if (bpp!=24) Fatal("%s bits per pixel is not 24: %d\n",file,bpp);
//    if (k!=0)    Fatal("%s compressed files not supported\n",file);
// #ifndef GL_VERSION_2_0
//    //  OpenGL 2.0 lifts the restriction that texture size must be a power of two
//    for (k=1;k<dx;k*=2);
//    if (k!=dx) Fatal("%s image width not a power of two: %d\n",file,dx);
//    for (k=1;k<dy;k*=2);
//    if (k!=dy) Fatal("%s image height not a power of two: %d\n",file,dy);
// #endif

//    //  Allocate image memory
//    unsigned int size = 3*dx*dy;
//    unsigned char* image = (unsigned char*) malloc(size);
//    if (!image) Fatal("Cannot allocate %d bytes of memory for image %s\n",size,file);
//    //  Seek to and read image
//    if (fseek(f,off,SEEK_SET) || fread(image,size,1,f)!=1) Fatal("Error reading data from image %s\n",file);
//    fclose(f);
//    //  Reverse colors (BGR -> RGB)
//    for (k=0;k<size;k+=3)
//    {
//       unsigned char temp = image[k];
//       image[k]   = image[k+2];
//       image[k+2] = temp;
//    }

//    //  Sanity check
//    ErrCheck("LoadTexBMP");
//    //  Generate 2D texture
//    unsigned int texture;
//    glGenTextures(1,&texture);
//    glBindTexture(GL_TEXTURE_2D,texture);
//    //  Copy image
//    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);
//    if (glGetError()) Fatal("Error in glTexImage2D %s %dx%d\n",file,dx,dy);
//    //  Scale linearly when image size doesn't match
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

//    //  Free image memory
//    free(image);
//    //  Return texture name
//    return texture;
// }