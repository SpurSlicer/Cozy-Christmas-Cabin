#include "house.h"

House::House() {
    this->generateShader("transp", "__snow.vert", "__snow.frag");
    this->generateTexture("log", "_log.png");
    this->generateTexture("floor", "_wood_floor.png");
    this->generateTexture("stone", "_stone_fireplace.png");
    this->generateTexture("basalt", "_basalt.png");
    this->generateTexture("mantle", "_mantle.png");
    this->generateTexture("tv", "_tv.png");
    this->generateTexture("door", "_door.png");
    this->generateTexture("rug", "_rug.png");
    this->generateTexture("ashes", "_ashes.png");

    this->generateTexture("smoke", "_smoke.png");
    this->generateTexture("alpha_smoke", "_alpha_smoke.png");

    this->generateTexture("cloud", "_noise2.png");
    this->generateTexture("noise", "_noise2.png");
    this->generateTexture("fire", "_fire.png");
    this->generateTexture("alpha", "_alpha.png");

    this->generateTexture("alpha_circ", "_alpha_circ.png");

    this->generateTexture("stocking", "_stocking.png");
    this->generateTexture("pic_1", "_pic_1.png");
    this->generateTexture("pic_2", "_pic_2.png");
    this->generateTexture("pic_3", "_pic_3.png");
    this->generateTexture("pic_4", "_pic_4.png");

    this->generateShader("fire", "__fire.vert", "__fire.frag");
    this->generateShader("ash", "__ash.vert", "__ash.frag");
    // this->generateShader("tv", "__tv.vert", "__tv.frag");
    this->generateShader("smoke", "__smoke.vert", "__smoke.frag");
    this->generateShader("default", "__default.vert", "__default.frag");
    this->arm_chair = new ArmChair();
    this->bookshelf = new Bookshelf();

    this->is_extinguished = false;
}

void House::drawCylinder(double length) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("log");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    
    coordinate* c1 = nullptr,* c2 = nullptr,* c3 = nullptr,* c4 = nullptr;
    const int factor = 360/12;
    int tex_index = 1;
    const float frac = length/5.0;
    for (int a = 0; a < 360; a += factor) {
        c1 = new coordinate({Cos(a)/2, Sin(a)/2, 0});
        c2 = new coordinate({Cos(a)/2, Sin(a)/2, length});
        a += factor;
        c3 = new coordinate({Cos(a)/2, Sin(a)/2, length});
        c4 = new coordinate({Cos(a)/2, Sin(a)/2, 0});
        coordinate* normal = nullptr;
        a -= factor;
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        normal = generateNormalBySquare(c1, c2, c3, c4);
        glNormal3f(normal->x, normal->y, normal->z);
        glVertex3f(Cos(a)/2, Sin(a)/2, 0);
        glTexCoord2f(0, (tex_index-1.0)/length);
        glVertex3f(Cos(a)/2, Sin(a)/2, length);
        glTexCoord2f(0, tex_index/length);
        a += factor;
        glVertex3f(Cos(a)/2, Sin(a)/2, length);
        glTexCoord2f(frac, tex_index/length);
        glVertex3f(Cos(a)/2, Sin(a)/2, 0);
        glTexCoord2f(frac, (tex_index-1.0)/length);
        a -= factor;
        glEnd();
        delete c1;
        delete c2;
        delete c3;
        delete c4;
        delete normal;
        tex_index++;
    } 
    for (double offset = 0; offset <= (length); offset += length) {
        glBegin(GL_POLYGON);
        //if (offset = 0) glNormal3f(0.0, -1.0, 0.0); // MINUS_Y
        //else glNormal3f(0.0, 1.0, 0.0); // PLUS_Y
        for (double a = 0; a <= 360; a += factor)
            glVertex3f(Cos(a)/2, Sin(a)/2, offset);
        glEnd();
    }
    this->disableTextures();
}

void House::drawFire() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->YELLOW);
// LOG
    glPushMatrix();
    glTranslatef(11.25,  0.125, 26.15);
    // glTranslatef(12.0, 1.0, 15.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glScalef(0.75, 0.75, 0.75);
    drawCylinder(3.5);
    glPopMatrix();
    if (!this->is_extinguished) {
// FIRE    
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        //printf("%d\n", this->textures["fire"]);
        this->enableShaderWTick("fire");
        int id = glGetUniformLocation(this->shaders["fire"],"noise_tex");
        glUniform1i(id, 0);
        id = glGetUniformLocation(this->shaders["fire"],"fire_tex");
        glUniform1i(id, 1);
        id = glGetUniformLocation(this->shaders["fire"],"alpha_tex");
        glUniform1i(id, 2);
        this->enableTextures();
        this->applyTexture("noise", 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        this->applyTexture("fire", 1);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        this->applyTexture("alpha", 2);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
        glMultiTexCoord2f(GL_TEXTURE0, 0.0, 0.0);
        glMultiTexCoord2f(GL_TEXTURE1, 0.0, 0.0);
        glMultiTexCoord2f(GL_TEXTURE2, 0.0, 0.0);
        glVertex3d(10.0, 0.4, 26.0);
        glMultiTexCoord2f(GL_TEXTURE0, 0.0, 1.0);
        glMultiTexCoord2f(GL_TEXTURE1, 0.0, 1.0);
        glMultiTexCoord2f(GL_TEXTURE2, 0.0, 1.0);
        glVertex3d(10.0, 5.4, 26.0);
        glMultiTexCoord2f(GL_TEXTURE0, 1.0, 1.0);
        glMultiTexCoord2f(GL_TEXTURE1, 1.0, 1.0);
        glMultiTexCoord2f(GL_TEXTURE2, 1.0, 1.0);
        glVertex3d(14.8, 5.4, 26.0);
        glMultiTexCoord2f(GL_TEXTURE0, 1.0, 0.0);
        glMultiTexCoord2f(GL_TEXTURE1, 1.0, 0.0);
        glMultiTexCoord2f(GL_TEXTURE2, 1.0, 0.0);
        glVertex3d(14.8, 0.4, 26.0);
        glEnd();
        glActiveTexture(GL_TEXTURE0);
        this->disableTextures();
        this->disableShader();
        glDisable(GL_BLEND);
    } else {
// SMOKE 
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        //printf("%d\n", this->textures["fire"]);
        this->enableShaderWTick("smoke");
        int id = glGetUniformLocation(this->shaders["smoke"],"smoke_tex");
        glUniform1i(id, 0);
        id = glGetUniformLocation(this->shaders["smoke"],"alpha_tex");
        glUniform1i(id, 1);
        this->enableTextures();
        this->applyTexture("smoke", 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        this->applyTexture("alpha_smoke", 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
        glMultiTexCoord2f(GL_TEXTURE0, 0.0, 0.0);
        glMultiTexCoord2f(GL_TEXTURE1, 0.0, 0.0);
        glVertex3d(11.0, 0.0, 26.0);
        glMultiTexCoord2f(GL_TEXTURE0, 0.0, 1.0);
        glMultiTexCoord2f(GL_TEXTURE1, 0.0, 1.0);
        glVertex3d(11.0, 7.5, 26.0);
        glMultiTexCoord2f(GL_TEXTURE0, 1.0, 1.0);
        glMultiTexCoord2f(GL_TEXTURE1, 1.0, 1.0);
        glVertex3d(14.0, 7.5, 26.0);
        glMultiTexCoord2f(GL_TEXTURE0, 1.0, 0.0);
        glMultiTexCoord2f(GL_TEXTURE1, 1.0, 0.0);
        glVertex3d(14.0, 0.0, 26.0);
        glEnd();
        glActiveTexture(GL_TEXTURE0);
        this->disableTextures();
        this->disableShader();
        glDisable(GL_BLEND);
    }
}

void House::drawStockings() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableShader("transp");
    int id = glGetUniformLocation(this->shaders["transp"],"v_min");
    glUniform4f(id, 0.0, 0.0, 0.0, -1.0);
    id = glGetUniformLocation(this->shaders["transp"], "u_flag");
    glUniform1f(id, 1.0);
    this->enableTextures();
    this->applyTexture("stocking", 0);
    for (double  i = 0; i <= 8; i += 2) {
        if (i == 4) i += 1.5;
        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(7.5+i, 5.0, 23.45);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(7.5+i, 8.0, 23.45);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(10.0+i, 8.0, 23.45);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(10.0+i, 5.0, 23.45);
        glEnd();
    }
    this->disableTextures();
    this->disableShader();
}

void House::drawPictureFrames() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    // this->enableShader("transp");
    // int id = glGetUniformLocation(this->shaders["transp"],"v_min");
    // glUniform4f(id, 1.0, 1.0, 1.0, -1.0);
    this->applyTexture("pic_3", 0);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0); // PLUS_X
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.6, 4.0, 17.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.6, 8.0, 17.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.6, 8.0, 23.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.6, 4.0, 23.0);
    glEnd();
    this->applyTexture("pic_4", 0);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0); // PLUS_X
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.6, 2.0, 4.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.6, 4.0, 4.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.6, 4.0, 7.5);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.6, 2.0, 7.5);
    glEnd();
    this->applyTexture("pic_1", 0);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0); // PLUS_X
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.6, 6.0, 2.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(0.6, 9.0, 2.5);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.6, 9.0, 6.5);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.6, 6.0, 6.5);
    glEnd();
    this->disableTextures();
    // this->disableShader();
}

void House::drawSky() {
    this->enableShader("default");
    int id = glGetUniformLocation(this->shaders["default"],"tex");
    glUniform1i(id, 0);
    this->enableTextures();
    this->applyTexture("cloud");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-200.0, 20.0, -200.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-200.0, 20.0, 200.0);
    glTexCoord2f(2.0, 1.0);
    glVertex3f(200.0, 20.0, 200.0);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(200.0, 20.0, -200.0);
    glEnd();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    for (int i = -1; i <= 1; i+=2) {
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(200.0*i, 20.0, -200.0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(200.0*i, 5.0, -200.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(200.0*i, 5.0, 200.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(200.0*i, 20.0, 200.0);
        glEnd();
    }
    for (int i = -1; i <= 1; i+=2) {
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-200.0, 20.0, 200.0*i);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-200.0, 5.0, 200.0*i);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(200.0, 5.0, 200.0*i);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(200.0, 20.0, 200.0*i);
        glEnd();
    }
    this->disableTextures();
    this->disableShader();
}

void House::drawDoorFrame() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("mantle");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    for (double j = 9.75; j <= 15.75; j += 5.0) {
        for (double k = -0.75; k <= 1.25; k += 1.50) {
            glBegin(GL_QUADS);
            glColor3f(0.388, 0.263, 0);
            glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
            glTexCoord2f(0.0, 0.0);
            glVertex3d(j, 0.0, k);
            glTexCoord2f(1.0, 0.0);
            glVertex3d(j, 8.25, k);
            glTexCoord2f(1.0, 1.0);
            glVertex3d(j+0.5, 8.25, k);
            glTexCoord2f(0.0, 1.0);
            glVertex3d(j+0.5, 0.0, k);
            glEnd();
        }
    }
    for (double j = 9.75; j <= 15.25; j += 0.5) {
        if (j == 10.75) j = 14.75;
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        if (j == 9.75 || j == 14.75) glNormal3f(-1.0, 0.0, 0.0); // MINUS_X
        glNormal3f(1.0, 0.0, 0.0); // PLUS_X
        glTexCoord2f(0.0, 0.0);
        glVertex3d(j, 0.0, -0.75);
        glTexCoord2f(0.0, 1.0);
        glVertex3d(j, 8.25, -0.75);
        glTexCoord2f(1.0, 1.0);
        glVertex3d(j, 8.25, 0.75);
        glTexCoord2f(1.0, 0.0);
        glVertex3d(j, 0.0, 0.75);
        glEnd();
    }
    for (double k = 7.75; k <= 8.25; k += 0.5) {
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        glNormal3f(0.0, -1.0, 0.0); // MINUS_Y
        glTexCoord2f(0.0, 0.0);
        glVertex3d(10.25, k, -0.75);
        glTexCoord2f(0.0, 1.0);
        glVertex3d(14.75, k, -0.75);
        glTexCoord2f(1.0, 1.0);
        glVertex3d(14.75, k, 0.75);
        glTexCoord2f(1.0, 0.0);
        glVertex3d(10.25, k, 0.75);
        glEnd();
    }
    for (double k = -0.75; k <= 1.25; k += 1.50) {
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        glNormal3f(0.0, 0.0, 1.0); // PLUS_Z
        glTexCoord2f(0.0, 0.0);
        glVertex3d(10.25, 7.75, k);
        glTexCoord2f(0.0, 1.0);
        glVertex3d(14.75, 7.75, k);
        glTexCoord2f(1.0, 1.0);
        glVertex3d(14.75, 8.25, k);
        glTexCoord2f(1.0, 0.0);
        glVertex3d(10.25, 8.25, k);
        glEnd();
    }
    this->applyTexture("door");   
    glBegin(GL_QUADS);
    glColor3f(0.388, 0.263, 0);
    glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
    glTexCoord2f(0.0, 0.0);
    glVertex3d(10.25, 0.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3d(10.25, 7.75, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(14.75, 7.75, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3d(14.75, 0.0, 0.0);
    glEnd();   
    this->disableTextures(); 
}

void House::drawWindowSills() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("mantle");   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    
    for (double j = 0; j <= 1.5; j += 1.5) {
        for (int k = 0; k <= 4; k += 4) {
            glBegin(GL_QUADS);
            glColor3f(0.388, 0.263, 0);
            glNormal3f(1.0, 0.0, 0.0); // PLUS_X
            glTexCoord2f(0.0, 0.0);
            glVertex3d(24.25+j, 3.75+k, 9.75);
            glTexCoord2f(0.0, 1.0);
            glVertex3d(24.25+j, 4.25+k, 9.75);
            glTexCoord2f(5.0, 1.0);
            glVertex3d(24.25+j, 4.25+k, 15.25);
            glTexCoord2f(5.0, 0.0);
            glVertex3d(24.25+j, 3.75+k, 15.25);
            glEnd();
        }
    }
    for (double j = 0; j <= 4; j += 4) {
        double k = 3.75 + j;
        const double bound = k + 0.5;
        for (; k <= bound; k += 0.5) {
            glBegin(GL_QUADS);
            glColor3f(0.388, 0.263, 0);
            glNormal3f(0.0, -1.0, 0.0); // MINUS_Y
            glTexCoord2f(0.0, 0.0);
            glVertex3d(24.25, k, 9.75);
            glTexCoord2f(0.0, 1.0);
            glVertex3d(25.75, k, 9.75);
            glTexCoord2f(5.0, 1.0);
            glVertex3d(25.75, k, 15.25);
            glTexCoord2f(5.0, 0.0);
            glVertex3d(24.25, k, 15.25);
            glEnd();
        }
    }
    for (double j = 9.75; j <= 15.25; j += 5.5) {
        for (int k = 0; k <= 4; k += 4) {
            glBegin(GL_QUADS);
            glColor3f(0.388, 0.263, 0);
            glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
            glTexCoord2f(0.0, 0.0);
            glVertex3d(24.25, 3.75+k, j);
            glTexCoord2f(0.0, 1.0);
            glVertex3d(24.25, 4.25+k, j);
            glTexCoord2f(5.0, 1.0);
            glVertex3d(25.75, 4.25+k, j);
            glTexCoord2f(5.0, 0.0);
            glVertex3d(25.75, 3.75+k, j);
            glEnd();
        }
    }
    // MAYBE BROKEN
    for (double j = 24.25; j <= 25.75; j += 1.5) {
        for (double k = 9.75; k <= 15.25; k += 5.0) {
            glBegin(GL_QUADS);
            glColor3f(0.388, 0.263, 0);
            glNormal3f(1.0, 0.0, 0.0); // PLUS_X
            glTexCoord2f(1.0, 0.0);
            glVertex3d(j, 4.25, k);
            glTexCoord2f(1.0, 5.0);
            glVertex3d(j, 7.75, k);
            glTexCoord2f(0.0, 5.0);
            glVertex3d(j, 7.75, k + 0.5);
            glTexCoord2f(0.0, 0.0);
            glVertex3d(j, 4.25, k + 0.5);
            glEnd();
        }
    }
    // ----
    for (double j = 0; j <= 5; j += 5) {
        double k = 9.75 + j;
        const double bound = k + 0.5;
        for (; k <= bound; k += 0.5) {
            glBegin(GL_QUADS);
            glColor3f(0.388, 0.263, 0);
            glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
            glTexCoord2f(0.0, 0.0);
            glVertex3d(24.25, 4.25, k);
            glTexCoord2f(1.0, 0.0);
            glVertex3d(24.25, 7.75, k);
            glTexCoord2f(1.0, -5.0);
            glVertex3d(25.75, 7.75, k);
            glTexCoord2f(0.0, -5.0);
            glVertex3d(25.75, 4.25, k);
            glEnd();
        }
    }
    this->disableTextures();
}

void House::drawWindowWalls() {
    for (double j = 0; j <= 25; j += 25) {
        for (int k = 0; k < 20; k++) {
            glPushMatrix();
            if (k > 3 && k < 8) {
                if (j == 0) {
                    //glRotatef(180.0, 1.0, 0.0, 0.0);
                    glTranslated(25.0, k+0.5, 0.0);
                    drawCylinder(10);
                    glPopMatrix();
                    glPushMatrix();
                    glTranslated(25.0, k+0.5, 15.0);
                    drawCylinder(10);
                } else {
                    glTranslated(0.0, k+0.5, 10.0);
                    glRotated(180, 0.0, 1.0, 0.0);
                    drawCylinder(10);
                    glPopMatrix();
                    glPushMatrix();
                    glTranslated(0.0, k+0.5, 25.0);
                    glRotated(180, 0.0, 1.0, 0.0);
                    drawCylinder(10);
                }
            } else {
                glPopMatrix();
                glPushMatrix();
                glTranslated(j, k+0.5, (j != 0) ? 25.0 : 0.0);
                if (j != 0) glRotated(180, 0.0, 1.0, 0.0);
                drawCylinder(25);
            }
            glPopMatrix();
        }
    }
    drawWindowSills();
    glPushMatrix();
    glTranslated(-25.0, 0.0, 0.0);
    drawWindowSills();
    glPopMatrix();
}

void House::drawDoorWall() {
    for (int k = 0; k < 20; k++) {
        glPushMatrix();
        glRotated(-90.0, 0.0, 1.0, 0.0);
        glTranslated(0, k+0.5, -25.0);
        if (k < 8) {
            glPopMatrix();
            glPushMatrix();
            glTranslated(0.0, k+0.5, 0.0);
            glRotated(90.0, 0.0, 1.0, 0.0);
            drawCylinder(10);
            glPopMatrix();
            glPushMatrix();
            glRotated(90.0, 0.0, 1.0, 0.0);
            glTranslated(0.0, k+0.5, 15.0);
            drawCylinder(10);
        } else {
            drawCylinder(25);
        }
        glPopMatrix();
    }
    drawDoorFrame();
}

void House::drawFirePlaceWall() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    for (int k = 0; k < 20; k++) {
        glPushMatrix();
        glTranslated(0.0, k+0.5, 25.0);
        glRotated(90.0, 0.0, 1.0, 0.0);
        if (k < 4) {
            glPopMatrix();
            glPushMatrix();
            glTranslated(25.0, k+0.5, 25.0);
            glRotated(270.0, 0.0, 1.0, 0.0);
            drawCylinder(10.25);
            glPopMatrix();
            glPushMatrix();
            glTranslated(10.25, k+0.5, 25.0);
            glRotated(270.0, 0.0, 1.0, 0.0);
            drawCylinder(10.25);
        } else {
            drawCylinder(25);
        }
        glPopMatrix();
    }

}
void House::drawMantle() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("mantle");   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    glBegin(GL_QUADS);
    glColor3f(0.169, 0.012, 0.012);
    glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
    glTexCoord2f(0.0, 0.0);
    glVertex3f(7.0, 7.5, 23.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(7.0, 8.25, 23.5);
    glTexCoord2f(6.0, 1.0);
    glVertex3f(18.0, 8.25, 23.5);
    glTexCoord2f(6.0, 0.0);
    glVertex3f(18.0, 7.5, 23.5);
    glEnd();
    for (double i = 0; i <= 11; i += 11) {
        glBegin(GL_QUADS);
        // if (i == 0) glNormal3f(1.0, 0.0, 0.0); // MINUS_X
        glNormal3f(1.0, 0.0, 0.0); // PLUS_X
        glColor3f(0.169, 0.012, 0.012);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(7.0+i, 7.5, 23.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(7.0+i, 8.25, 23.5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(7.0+i, 8.25, 24.25);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(7.0+i, 7.5, 24.25);
        glEnd();
    }
    glBegin(GL_QUADS);
    glColor3f(0.169, 0.012, 0.012);
    glNormal3f(0.0, 1.0, 0.0); // PLUS_Y
    glTexCoord2f(0.0, 0.0);
    glVertex3f(7.0, 7.5, 23.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(7.0, 7.5, 24.25);
    glTexCoord2f(6.0, 1.0);
    glVertex3f(18.0, 7.5, 24.25);
    glTexCoord2f(6.0, 0.0);
    glVertex3f(18.0, 7.5, 23.5);
    glEnd();
    this->disableTextures();
}
void House::drawTV() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->BLACK);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
    glVertex3f(9.5, 9.5, 23.8);
    glVertex3f(9.5, 12.5, 23.8);
    glVertex3f(15.5, 12.5, 23.8);
    glVertex3f(15.5, 9.5, 23.8);
    glEnd();
    for (double i = 0; i <= 6.5; i += 6.5) {
        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(9.0+i, 9.0, 23.5);
        glVertex3f(9.0+i, 13.0, 23.5);
        glVertex3f(9.5+i, 13.0, 23.5);
        glVertex3f(9.5+i, 9.0, 23.5);
        glEnd();
    }
    for (double i = 0; i <= 3.5; i += 3.5) {
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        glNormal3f(0.0, 0.0, 1.0); // PLUS_Z
        glVertex3f(9.5, 9.0+i, 23.5);
        glVertex3f(9.5, 9.5+i, 23.5);
        glVertex3f(15.5, 9.5+i, 23.5);
        glVertex3f(15.5, 9.0+i, 23.5);
        glEnd();
    }
    for (double i = 0; i <= 6.5; i += 6.5) {
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        glNormal3f(-1.0, 0.0, 0.0); // MINUS_X
        glVertex3f(9.0+i, 9.0, 23.5);
        glVertex3f(9.0+i, 13.0, 23.5);
        glVertex3f(9.0+i, 13.0, 24.25);
        glVertex3f(9.0+i, 9.0, 24.25);
        glEnd();
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        glNormal3f(1.0, 0.0, 0.0); // PLUS_X
        glVertex3f(9.5+i, 9.0, 23.5);
        glVertex3f(9.5+i, 13.0, 23.5);
        glVertex3f(9.5+i, 13.0, 24.25);
        glVertex3f(9.5+i, 9.0, 24.25);
        glEnd();
    }
    for (double i = 0; i <= 3.5; i += 3.5) {
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        glNormal3f(0.0, -1.0, 0.0); // MINUS_Y
        glVertex3f(9.0, 9.0+i, 23.5);
        glVertex3f(9.0, 9.0+i, 24.25);
        glVertex3f(16.0, 9.0+i, 24.25);
        glVertex3f(16.0, 9.0+i, 23.5);
        glEnd();        
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        glNormal3f(0.0, 1.0, 0.0); // PLUS_Y
        glVertex3f(9.0, 9.5+i, 23.5);
        glVertex3f(9.0, 9.5+i, 24.25);
        glVertex3f(16.0, 9.5+i, 24.25);
        glVertex3f(16.0, 9.5+i, 23.5);
        glEnd();
    }
    this->enableShader("default");
    int id = glGetUniformLocation(this->shaders["default"],"tex");
    glUniform1i(id, 0);
    this->enableTextures();
    this->applyTexture("tv");   
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glColor3f(1.0, 1.0, 1.0);  
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
    glTexCoord2f(1.0, 0.0);
    glVertex3f(9.5, 9.5, 23.75);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(9.5, 12.5, 23.75);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(15.5, 12.5, 23.75);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(15.5, 9.5, 23.75);
    glEnd();
    this->disableTextures();
    this->disableShader();
}
void House::drawHearth() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("basalt");   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, 0.0, 1.0); // PLUS_Z
    glTexCoord2f(0.0, 0.0);
    glVertex3d(9.5, 0.0, 23.5);
    glTexCoord2f(4.0, 0.0);
    glVertex3d(15.5, 0.0, 23.5);
    glTexCoord2f(4.0, 1.0);
    glVertex3d(15.5, 0.5, 23.5);
    glTexCoord2f(0.0, 1.0);
    glVertex3d(9.5, 0.5, 23.5);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, 0.0, 1.0); // PLUS_Z
    glTexCoord2f(0.0, 0.0);
    glVertex3d(10.5, 3.5, 24.25);
    glTexCoord2f(4.0, 0.0);
    glVertex3d(14.5, 3.5, 24.25);
    glTexCoord2f(4.0, 1.0);
    glVertex3d(14.5, 4, 24.25);
    glTexCoord2f(0.0, 1.0);
    glVertex3d(10.5, 4, 24.25);
    glEnd();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, 1.0, 0.0); // PLUS_Y
    glTexCoord2f(0.0, 0.0);
    glVertex3d(15.5, 0.5, 23.5);
    glTexCoord2f(2.0, 0.0);
    glVertex3d(9.5, 0.5, 23.5);
    glTexCoord2f(2.0, 1.0);
    glVertex3d(9.5, 0.5, 25.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3d(15.5, 0.5, 25.0);
    glEnd();
    this->enableShaderWTick("ash");
    int id = glGetUniformLocation(this->shaders["ash"],"ash_tex");
    glUniform1i(id, 0);
    id = glGetUniformLocation(this->shaders["ash"],"basalt_tex");
    glUniform1i(id, 1);
    id = glGetUniformLocation(this->shaders["ash"],"alpha_tex");
    glUniform1i(id, 2);
    this->applyTexture("ashes", 0);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);    
    this->applyTexture("basalt", 1);   
    this->applyTexture("alpha_circ", 2);   
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0, 0.0); // MINUS_Y
    glMultiTexCoord2f(GL_TEXTURE0, 0.0, 0.0);
    glMultiTexCoord2f(GL_TEXTURE1, 0.0, 0.0);
    glMultiTexCoord2f(GL_TEXTURE2, 0.0, 0.0);
    glVertex3d(14.5, 0.0, 25.0);
    glMultiTexCoord2f(GL_TEXTURE0, 1.0, 0.0);
    glMultiTexCoord2f(GL_TEXTURE1, 1.0, 0.0);
    glMultiTexCoord2f(GL_TEXTURE2, 1.0, 0.0);
    glVertex3d(10.5, 0.0, 25.0);
    glMultiTexCoord2f(GL_TEXTURE0, 1.0, 1.0);
    glMultiTexCoord2f(GL_TEXTURE1, 1.0, 1.0);
    glMultiTexCoord2f(GL_TEXTURE2, 1.0, 1.0);
    glVertex3d(10.5, 0.0, 27.5);
    glMultiTexCoord2f(GL_TEXTURE0, 0.0, 1.0);
    glMultiTexCoord2f(GL_TEXTURE1, 0.0, 1.0);
    glMultiTexCoord2f(GL_TEXTURE2, 0.0, 1.0);
    glVertex3d(14.5, 0.0, 27.5);
    glEnd();
    this->disableShader();
    glActiveTexture(GL_TEXTURE0);
    this->applyTexture("basalt");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    
    for (double i = 0; i <= 6; i += 6) {
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        if (i == 0) glNormal3f(-1.0, 0.0, 0.0); // MINUS_X
        else glNormal3f(1.0, 0.0, 0.0); // PLUS_X
        glTexCoord2f(0.0, 0.0);
        glVertex3d(9.5+i, 0.0, 23.5);
        glTexCoord2f(2.0, 0.0);
        glVertex3d(9.5+i, 0.5, 23.5);
        glTexCoord2f(2.0, 1.0);
        glVertex3d(9.5+i, 0.5, 28.5);
        glTexCoord2f(0.0, 1.0);
        glVertex3d(9.5+i, 0.0, 28.5);
        glEnd();
    }
    this->disableTextures();
}
void House::drawInsideOfFireplace() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("basalt");    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);  
    coordinate* c1 = new coordinate({10.5, 0.0, 24.25});
    coordinate* c2 = new coordinate({10.5, 3.5, 24.25});
    coordinate* c3 = new coordinate({11.5, 3.5, 27.5});
    coordinate* c4 = new coordinate({10.5, 0.0, 27.5});
    coordinate* normal = generateNormalBySquare(c1, c2, c3, c4);  
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(10.5, 0.0, 24.25);
    glTexCoord2f(0.0, 2.0);
    glVertex3d(10.5, 3.5, 24.25);
    glTexCoord2f(2.0, 2.0);
    glVertex3d(11.5, 3.5, 27.5);
    glTexCoord2f(2.0, 0.0);
    glVertex3d(10.5, 0.0, 27.5);
    glEnd();
    delete c1;
    delete c2;
    delete c3;
    delete c4; 
    delete normal;
    c1 = new coordinate({14.5, 0.0, 24.25});
    c2 = new coordinate({14.5, 3.5, 24.25});
    c3 = new coordinate({13.5, 3.5, 27.5});
    c4 = new coordinate({14.5, 0.0, 27.5});
    normal = generateNormalBySquare(c1, c2, c3, c4);  
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(14.5, 0.0, 24.25);
    glTexCoord2f(0.0, 2.0);
    glVertex3d(14.5, 3.5, 24.25);
    glTexCoord2f(2.0, 2.0);
    glVertex3d(13.5, 3.5, 27.5);
    glTexCoord2f(2.0, 0.0);
    glVertex3d(14.5, 0.0, 27.5);
    glEnd();
    delete c1;
    delete c2;
    delete c3;
    delete c4; 
    delete normal;
    c1 = new coordinate({10.5, 0.0, 27.5});
    c2 = new coordinate({11.5, 3.5, 27.5});
    c3 = new coordinate({13.5, 3.5, 27.5});
    c4 = new coordinate({14.5, 0.0, 27.5});
    normal = generateNormalBySquare(c1, c2, c3, c4);  
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(10.5, 0.0, 27.5);
    glTexCoord2f(0.0, 2.0);
    glVertex3d(11.5, 3.5, 27.5);
    glTexCoord2f(2.0, 2.0);
    glVertex3d(13.5, 3.5, 27.5);
    glTexCoord2f(2.0, 0.0);
    glVertex3d(14.5, 0.0, 27.5);
    glEnd();
    delete c1;
    delete c2;
    delete c3;
    delete c4; 
    delete normal;
    this->disableTextures();
}
void House::drawFirePlace() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("stone");    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    for (double i = 0; i <= +4; i += 4) {
        glBegin(GL_POLYGON);
        if (i == 0) glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
        else glNormal3f(0.0, 0.0, 1.0); // PLUS_Z
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord3f(10.5+i, 0.0, 24.25);
        glVertex3d(10.5+i, 0.0, 24.25);
        glTexCoord3f(8.0 + ((i > 0) ? (i+5) : (0)), 0.0, 24.25);
        glVertex3d(8.0 + ((i > 0) ? (i+5) : (0)), 0.0, 24.25);
        glTexCoord3f(((i > 0) ? (11.0) : (10.0))+i, 3.5, 24.25);
        glVertex3d(((i > 0) ? (11.0) : (10.0))+i, 3.5, 24.25);
        glTexCoord3f(((i > 0) ? (11.0) : (10.0))+i, 4.0, 24.25);
        glVertex3d(((i > 0) ? (11.0) : (10.0))+i, 4.0, 24.25);
        glTexCoord3f(10.5+i, 4.0, 24.25);
        glVertex3d(10.5+i, 4.0, 24.25);
        glEnd();
    }
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord3f(10.0, 4.0, 24.25);
    glVertex3f(10.0, 4.0, 24.25);
    glTexCoord3f(10.75, 7.5, 24.25);
    glVertex3f(10.75, 7.5, 24.25);
    glTexCoord3f(14.25, 7.5, 24.25);
    glVertex3f(14.25, 7.5, 24.25);
    glTexCoord3f(15.0, 4.0, 24.25);
    glVertex3f(15.0, 4.0, 24.25);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord3f(11.0, 7.5, 24.25);
    glVertex3f(11.0, 7.5, 24.25);
    glTexCoord3f(11.0, 15.0, 24.25);
    glVertex3f(11.0, 15.0, 24.25);
    glTexCoord3f(14.0, 15.0, 24.25);
    glVertex3f(14.0, 15.0, 24.25);
    glTexCoord3f(14.0, 7.5, 24.25);
    glVertex3f(14.0, 7.5, 24.25);
    glEnd();
    coordinate* c1 = new coordinate({1.5, 11.5, 12.0});
    coordinate* c2 = new coordinate({1.5, 11.5, 13.0});
    coordinate* c3 = new coordinate({12.0, 14.0, 13.0});
    coordinate* c4 = new coordinate({12.0, 14.0, 12.0});
    coordinate* normal = generateNormalBySquareFLIP(c1, c2, c3, c4);
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord3f(0.0, 0.0, 24.25);
    glVertex3f(8.0, 0.0, 24.25);
    glTexCoord3f(0.0, 4.0, 24.25);
    glVertex3f(10.5, 3.5, 24.25);
    glTexCoord3f(1.0, 4.0, 26.25);
    glVertex3f(10.5, 3.5, 26.25);
    glTexCoord3f(1.0, 0.0, 26.25);
    glVertex3f(8.0, 0.0, 26.25);
    glEnd();
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete normal;
    c1 = new coordinate({1.5, 11.5, 12.0});
    c2 = new coordinate({1.5, 11.5, 13.0});
    c3 = new coordinate({12.0, 14.0, 13.0});
    c4 = new coordinate({12.0, 14.0, 12.0});
    normal = generateNormalBySquareFLIP(c1, c2, c3, c4);
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord3f(0.0, 0.0, 24.25);
    glVertex3f(17.0, 0.0, 24.25);
    glTexCoord3f(0.0, 4.0, 24.25);
    glVertex3f(14.5, 3.5, 24.25);
    glTexCoord3f(1.0, 4.0, 26.25);
    glVertex3f(14.5, 3.5, 26.25);
    glTexCoord3f(1.0, 0.0, 26.25);
    glVertex3f(17.0, 0.0, 26.25);
    glEnd();
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete normal;
    for (double i = 0; i <= 4; i += 4) {
        glBegin(GL_QUADS);
        glNormal3f(+1.0, 0.0, 0.0); // PLUS_X
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(10.5+i, 3.5, 24.25);
        glTexCoord2f(0.0, 0.35);
        glVertex3f(10.5+i, 4.0, 24.25);
        glTexCoord2f(1.0, 0.35);
        glVertex3f(10.5+i, 4.0, 26.25);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(10.5+i, 3.5, 26.25);
        glEnd();
    }
    c1 = new coordinate({10.0, 4.0, 24.25});
    c2 = new coordinate({10.75, 7.5, 24.25});
    c3 = new coordinate({10.75, 7.5, 26.25});
    c4 = new coordinate({10.0, 4.0, 26.25});
    normal = generateNormalBySquare(c1, c2, c3, c4);
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(10.0, 4.0, 24.25);
    glTexCoord2f(0.0, 5.0);
    glVertex3f(10.75, 7.5, 24.25);
    glTexCoord2f(1.0, 5.0);
    glVertex3f(10.75, 7.5, 26.25);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(10.0, 4.0, 26.25);
    glEnd();    
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete normal;
    c1 = new coordinate({15.0, 4.0, 24.25});
    c2 = new coordinate({14.25, 7.5, 24.25});
    c3 = new coordinate({14.25, 7.5, 26.25});
    c4 = new coordinate({15.0, 4.0, 26.25});
    normal = generateNormalBySquare(c1, c2, c3, c4);
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(15.0, 4.0, 24.25);
    glTexCoord2f(0.0, 5.0);
    glVertex3f(14.25, 7.5, 24.25);
    glTexCoord2f(1.0, 5.0);
    glVertex3f(14.25, 7.5, 26.25);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(15.0, 4.0, 26.25);
    glEnd();
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete normal;
    for (double i = 0; i <= 3; i += 3) {
        glBegin(GL_QUADS);
        glNormal3f(1.0, 0.0, 0.0); // PLUS_X
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord3f(11.0+i, 7.5, 24.25);
        glVertex3f(11.0+i, 7.5, 24.25);
        glTexCoord3f(11.0+i, 15.0, 24.25);
        glVertex3f(11.0+i, 15.0, 24.25);
        glTexCoord3f(11.0+i, 15.0, 26.25);
        glVertex3f(11.0+i, 15.0, 26.25);
        glTexCoord3f(11.0+i, 7.5, 26.25);
        glVertex3f(11.0+i, 7.5, 26.25);
        glEnd();
    }
    this->disableTextures();
    drawInsideOfFireplace();
    drawHearth();
    drawMantle();
    drawTV();
}


void House::drawFloor() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("floor");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0); // MINUS_Y
    glColor3f(0.388, 0.263, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2f(0.0, 6.0);
    glVertex3f(25.0, 0.0, 0.0);
    glTexCoord2f(6.0, 6.0);
    glVertex3f(25.0, 0.0, 25.0);
    glTexCoord2f(6.0, 0.0);
    glVertex3f(0.0, 0.0, 25.0);
    glEnd();
    this->disableTextures();
}

void House::drawRoof() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("mantle");    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    
    coordinate* c1 = nullptr,* c2 = nullptr,* c3 = nullptr,* c4 = nullptr;
    for (int i = 0; i <= LENGTH; i += LENGTH) {
        c1 = new coordinate({(double)i, 12.5, 0.0});
        c2 = new coordinate({LENGTH/2, 15.0, 0.0});
        c3 = new coordinate({LENGTH/2, 15.0, LENGTH});
        c4 = new coordinate({(double)i, 12.5, LENGTH});
        coordinate* normal = nullptr;
        glBegin(GL_QUADS);
        if (i == 0) normal = generateNormalBySquare(c1, c2, c3, c4);
        else normal = generateNormalBySquare(c1, c2, c3, c4);
        glColor3f(0.388, 0.263, 0);
        glNormal3f(normal->x, normal->y, normal->z);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(i, 12.5, 0.0);
        glTexCoord2f(0.0, 6.0);
        glVertex3f(LENGTH/2, 15.0, 0.0);
        glTexCoord2f(6.0, 6.0);
        glVertex3f(LENGTH/2, 15.0, LENGTH);
        glTexCoord2f(6.0, 0.0);
        glVertex3f(i, 12.5, LENGTH);
        glEnd();
        delete c1;
        delete c2;
        delete c3;
        delete c4;
        delete normal;
    }
    this->disableTextures();
    this->enableTextures();
    this->applyTexture("mantle");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glBegin(GL_QUADS);
    glColor3f(0.388, 0.263, 0);
    glNormal3f(0.0, 1.0, 0.0); // PLUS_Y
    glTexCoord2f(0.0, 0.0);
    glVertex3f(12.0, 14.0, 0.0);
    glTexCoord2f(0.0, 10.0);
    glVertex3f(12.0, 14.0, 25.0);
    glTexCoord2f(1.0, 10.0);
    glVertex3f(13.0, 14.0, 25.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(13.0, 14.0, 0.0);
    glEnd();
    for (int i = 0; i < 2; i++) {
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        // if (i == 0) glNormal3f(-1.0, 0.0, 0.0); // MINUS_X
        glNormal3f(1.0, 0.0, 0.0); // PLUS_X
        glTexCoord2f(0.0, 0.0);
        glVertex3f(12.0+i, 14.0, 0.0);
        glTexCoord2f(0.0, 10.0);
        glVertex3f(12.0+i, 14.0, 25.0);
        glTexCoord2f(1.0, 10.0);
        glVertex3f(12.0+i, 15.0, 25.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(12.0+i, 15.0, 0.0);
        glEnd(); 
    }
    for (int i = 0; i < 25; i += 23.5) {
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        glNormal3f(0.0, 1.0, 0.0); // PLUS_Y
        glTexCoord2f(0.0, 0.0);
        glVertex3f(0.0+i, 11.5, 0.0);
        glTexCoord2f(0.0, 10.0);
        glVertex3f(0.0+i, 11.5, 25.0);
        glTexCoord2f(1.0, 10.0);
        glVertex3f(1.5+i, 11.5, 25.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.5+i, 11.5, 0.0);
        glEnd();
        int j = 0.0;
        if (i != 0) j = 22.0;
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        // if (i == 0) glNormal3f(1.0, 0.0, 0.0); // PLUS_X
        glNormal3f(-1.0, 0.0, 0.0); // MINUS_X
        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.5+j, 11.5, 0.0);
        glTexCoord2f(1.0, 10.0);
        glVertex3f(1.5+j, 11.5, 25.0);
        glTexCoord2f(1.0, 10.0);
        glVertex3f(1.5+j, 12.5, 25.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.5+j, 12.5, 0.0);
        glEnd();
    }

    for (int i = 0; i < 2; i++) {
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        // if (i == 0) glNormal3f(0.0, 0.0, 1.0); // PLUS_Z
        glNormal3f(0.0, 0.0, 1.0); // PLUS_Z
        glTexCoord2f(0.0, 0.0);
        glVertex3f(1.5, 11.5, 12.0+i);
        glTexCoord2f(0.0, 10.0);
        glVertex3f(12.0, 14.0, 12.0+i);
        glTexCoord2f(1.0, 10.0);
        glVertex3f(12.0, 15.0, 12.0+i);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.5, 12.5, 12.0+i);
        glEnd(); 
    }
    c1 = new coordinate({1.5, 11.5, 12.0});
    c2 = new coordinate({1.5, 11.5, 13.0});
    c3 = new coordinate({12.0, 14.0, 13.0});
    c4 = new coordinate({12.0, 14.0, 12.0});
    coordinate* normal = generateNormalBySquare(c1, c2, c3, c4);
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);
    glColor3f(0.388, 0.263, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.5, 11.5, 12.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.5, 11.5, 13.0);
    glTexCoord2f(10.0, 1.0);
    glVertex3f(12.0, 14.0, 13.0);
    glTexCoord2f(10.0, 0.0);
    glVertex3f(12.0, 14.0, 12.0);
    glEnd();
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete normal;
    c1 = new coordinate({23.5, 11.5, 12.0});
    c2 = new coordinate({23.5, 11.5, 13.0});
    c3 = new coordinate({13.0, 14.0, 13.0});
    c4 = new coordinate({13.0, 14.0, 12.0});
    normal = generateNormalBySquare(c1, c2, c3, c4);
    glBegin(GL_QUADS);
    glNormal3f(normal->x, normal->y, normal->z);    glColor3f(0.388, 0.263, 0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(23.5, 11.5, 12.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(23.5, 11.5, 13.0);
    glTexCoord2f(10.0, 1.0);
    glVertex3f(13.0, 14.0, 13.0);
    glTexCoord2f(10.0, 0.0);
    glVertex3f(13.0, 14.0, 12.0);
    glEnd();
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete normal;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.263, 0);
        // if (i == 0) glNormal3f(0.0, 0.0, 1.0); // PLUS_Z
        glNormal3f(0.0, 0.0, -1.0); // MINUS_Z
        glTexCoord2f(0.0, 0.0);
        glVertex3f(23.5, 11.5, 12.0+i);
        glTexCoord2f(0.0, 10.0);
        glVertex3f(13.0, 14.0, 12.0+i);
        glTexCoord2f(1.0, 10.0);
        glVertex3f(13.0, 15.0, 12.0+i);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(23.5, 12.5, 12.0+i);
        glEnd(); 
    }
    this->disableTextures();
}

void House::drawRug() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    // this->enableShader("transp");
    // int id = glGetUniformLocation(this->shaders["transp"],"v_min");
    // glUniform4f(id, 0.90, 0.90, 0.90, 1.0);
    this->enableTextures();
    this->applyTexture("rug");    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, -1.0, 0.0); // PLUS_Y
    glTexCoord2f(0.0, 0.0);
    glVertex3f(10.0, 0.1, 6.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(10.0, 0.1, 17.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(2.0, 0.1, 17.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(2.0, 0.1, 6.0);
    glEnd();
    this->disableTextures();
    // this->disableShader();
}

void House::draw() {
    //this->enableShader("phong");
    this->updateTick();
    this->drawWindowWalls();
    this->drawDoorWall();
    this->drawFirePlaceWall();
    this->drawFirePlace();
    this->drawFloor();
    this->drawRoof();
    this->drawFire();
    this->drawRug();
    this->drawSky();
    this->drawStockings();
    this->drawPictureFrames();
    this->arm_chair->draw();
    this->bookshelf->draw();
    //this->disableShader();
}

void House::toggleExtinguishState() {
    this->is_extinguished = !this->is_extinguished;
}