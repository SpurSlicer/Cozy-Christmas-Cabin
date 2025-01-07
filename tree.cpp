#include "tree.h"

Tree::Tree() {
    //this->generateShader("phong", "pixlight.vert", "pixlight.frag");
    this->generateTexture("log", "_log.png");
    this->generateTexture("tree", "_tree.png");
    this->generateTexture("star", "_star.png");
    this->generateTexture("treeskirt", "_treeskirt.png");
}

void Tree::drawTreeTrunk(double height) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("log");  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    
    const int factor = 360/18;
    const double scalar = 0.75;
    int tex_index = 1;
    coordinate* c1 = nullptr,* c2 = nullptr,* c3 = nullptr;
    for (int a = 0; a < 360; a += factor) {
        double cos_v = Cos(a) * scalar;
        double sin_v = Sin(a) * scalar;
        double cos_v_f = Cos(a+factor) * scalar;
        double sin_v_f = Sin(a+factor) * scalar;
        c1 = new coordinate({cos_v, 0, sin_v});
        c2 = new coordinate({0, height, 0});
        c3 = new coordinate({cos_v_f, 0, sin_v_f});
        coordinate* normal = nullptr;
        glBegin(GL_POLYGON);
        glColor3f(0.388, 0.263, 0);
        normal = generateNormalByTriangle(c1, c2, c3);
        glNormal3f(normal->x, normal->y, normal->z);
        glTexCoord2f((tex_index-1.0)/18.0, 0.0);
        glVertex3f(cos_v, 0, sin_v);
        glTexCoord2f(0.5, 1.0);
        glVertex3f(0, height, 0);
        glTexCoord2f(tex_index/18.0, 0.0);
        glVertex3f(cos_v_f, 0, sin_v_f);
        glEnd();
        delete c1;
        delete c2;
        delete c3;
        delete normal;
        tex_index++;
    } 
    this->disableTextures();
}
/* NEEDS REAL NORMALS */
void Tree::drawBranches(double height_max) {
    glMaterialf(GL_FRONT, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("tree");  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    int denominator = 18;
    double height = 1.5;
    double mult = height_max-1.5;
    const double height_increment = 0.4;
    double scalar = 4.0;
    coordinate* c1 = nullptr,* c2 = nullptr,* c3 = nullptr;
    for (; height < height_max; height += height_increment) {
        const double factor = 360.0/denominator;
        for (double a = 0.0; a < 360.0; a += factor) {
            double prop = mult/height_max;
            double cos_v = Cos(a) * (prop);
            double sin_v = Sin(a) * (prop);
            double cos_v_f = Cos(a+factor) * (prop);
            double sin_v_f = Sin(a+factor) * (prop);
            double cos_v_midpoint = (cos_v+cos_v_f)/2;
            double sin_v_midpoint = (sin_v+sin_v_f)/2;
            mult -= height_increment;
            prop = mult/height_max;
            double cos_v_midpoint_m = ((Cos(a) + Cos(a+factor)) / 2) * (prop);
            double sin_v_midpoint_m = ((Sin(a) + Sin(a+factor)) / 2) * (prop);
            c1 = new coordinate({cos_v, height, sin_v});
            c2 = new coordinate({cos_v_midpoint*scalar, height, sin_v_midpoint*scalar});
            c3 = new coordinate({cos_v_f, height, sin_v_f});
            coordinate* normal = nullptr;
            glBegin(GL_POLYGON);
            glColor3f(0, 0.439, 0.012);
            glNormal3f(0.0, -1.0, 0.0); // MINUS_Y
            glTexCoord2f(0.0, 0.0);
            glVertex3f(cos_v, height, sin_v);
            glTexCoord2f(0.5, 1.0);
            glVertex3f(cos_v_midpoint*scalar, height, sin_v_midpoint*scalar);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(cos_v_f, height, sin_v_f);
            glEnd();
            delete c1;
            delete c2;
            delete c3;
            c1 = new coordinate({cos_v, height, sin_v});
            c2 = new coordinate({cos_v_midpoint_m, height+height_increment, sin_v_midpoint_m});
            c3 = new coordinate({cos_v_midpoint*scalar, height, sin_v_midpoint*scalar});
            normal = this->generateNormalByTriangleFLIP(c1, c2, c3);
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
            glBegin(GL_POLYGON);
            // glNormal3f(normal->x, normal->y, normal->z);
            glNormal3f(0.0, -1.0, 0.0); // MINUS_Y
            glColor3f(0, 0.439, 0.012);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(cos_v, height, sin_v);
            glTexCoord2f(0.5, 1.0);
            glVertex3f(cos_v_midpoint_m, height+height_increment+1.0, sin_v_midpoint_m);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(cos_v_midpoint*scalar, height, sin_v_midpoint*scalar);
            glEnd();
            glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
            delete c1;
            delete c2;
            delete c3;
            // delete normal;
            c1 = new coordinate({cos_v_f, height, sin_v_f});
            c2 = new coordinate({cos_v_midpoint_m, height+height_increment, sin_v_midpoint_m});
            c3 = new coordinate({cos_v_midpoint*scalar, height, sin_v_midpoint*scalar});
            // normal = this->generateNormalByTriangleFLIP(c1, c2, c3);
            glColor3f(0, 0.439, 0.012);
            glBegin(GL_POLYGON);
            // glNormal3f(normal->x, normal->y, normal->z);
            glNormal3f(0.0, 1.0, 0.0); // MINUS_Y
            glTexCoord2f(0.0, 0.0);
            glVertex3f(cos_v_f, height, sin_v_f);
            glTexCoord2f(0.5, 1.0);
            glVertex3f(cos_v_midpoint_m, height+height_increment+1.0, sin_v_midpoint_m);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(cos_v_midpoint*scalar, height, sin_v_midpoint*scalar);
            glEnd();
            delete c1;
            delete c2;
            delete c3;
            delete normal;
            
            mult += height_increment;
            // break;
        }
        if ((denominator - 1 > 2)) denominator--;
        if (mult - height_increment > 0) mult -= height_increment;
    }
    this->disableTextures();
}
void Tree::drawStar() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("star");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    const int factor = 360/5;
    const double min_scalar = 0.5;
    const double max_scalar = 1.5;
    coordinate* c1 = nullptr,* c2 = nullptr,* c3 = nullptr;
    for (int a = 0; a < 360; a += factor) {
        double cos_v = Cos(a)*min_scalar;
        double sin_v = Sin(a)*min_scalar;
        double cos_v_f = Cos(a+factor)*min_scalar;
        double sin_v_f = Sin(a+factor)*min_scalar;
        double cos_v_midpoint = (Cos(a)+Cos(a+factor))/2;
        double sin_v_midpoint = (Sin(a)+Sin(a+factor))/2;
        for (int s = -1; s <= 1; s += 2) {
            c1 = new coordinate({cos_v, sin_v, 0.0});
            c2 = new coordinate({0.0, 0.0, s*0.5});
            c3 = new coordinate({cos_v_midpoint*max_scalar, sin_v_midpoint*max_scalar, 0.0});
            coordinate* normal = generateNormalByTriangle(c2, c3, c1);
            glColor3f(0.996, 1, 0);
            glBegin(GL_POLYGON);
            //glColor3f(0.388, 0.224, 0);
            glNormal3f(normal->x, normal->y, normal->z);
            glTexCoord3f(cos_v, sin_v, 0.0);
            glVertex3f(cos_v, sin_v, 0.0);
            glTexCoord3f(0.0, 0.0, s*0.5);
            glVertex3f(0.0, 0.0, s*0.5);
            glTexCoord3f(cos_v_midpoint*max_scalar, sin_v_midpoint*max_scalar, 0.0);
            glVertex3f(cos_v_midpoint*max_scalar, sin_v_midpoint*max_scalar, 0.0);
            glEnd();
            delete c1;
            delete c2;
            delete c3;
            delete normal;
            c1 = new coordinate({cos_v_f, sin_v_f, 0.0});
            c2 = new coordinate({0.0, 0.0, s*0.5});
            c3 = new coordinate({cos_v_midpoint*max_scalar, sin_v_midpoint*max_scalar, 0.0});
            normal = this->generateNormalByTriangleFLIP(c1, c3, c2);
            glColor3f(0.996, 1, 0);
            glBegin(GL_POLYGON);
            glNormal3f(normal->x, normal->y, normal->z);
            glTexCoord3f(cos_v_f, sin_v_f, 0);
            glVertex3f(cos_v_f, sin_v_f, 0);
            glTexCoord3f(0.0, 0.0, s*0.5);
            glVertex3f(0.0, 0.0, s*0.5);
            glTexCoord3f(cos_v_midpoint*max_scalar, sin_v_midpoint*max_scalar, 0.0);
            glVertex3f(cos_v_midpoint*max_scalar, sin_v_midpoint*max_scalar, 0.0);
            glEnd();
            delete c1;
            delete c2;
            delete c3;
            delete normal;
        }
        // break;
    } 
    this->disableTextures();
}

void Tree::drawTreeSkirt() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    this->applyTexture("treeskirt");  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);    
    const int factor = 360/18;
    int tex_index = 1;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (int a = 0; a < 360;) {
        glNormal3f(0.0, -1.0, 0.0); // MINUS_Y
        glTexCoord2f(Cos(a)/2+0.5, Sin(a)/2+0.5);
        glVertex3f(Cos(a)*4, 0.1, Sin(a)*4);
        a += factor;
        glTexCoord2f(Cos(a)/2+0.5, Sin(a)/2+0.5);
        glVertex3f(Cos(a)*4, 0.1, Sin(a)*4);
        tex_index++;
    } 
    glEnd();
    this->disableTextures();
}

void Tree::draw() {
    const double height = 9.0;
    this->updateTick();
    glPushMatrix();
    glTranslated(20.0, 0.0, 6.0);
    drawTreeTrunk(height);
    drawBranches(height);
    drawTreeSkirt();
    glPopMatrix();
    glPushMatrix();
    glTranslated(20.0, height+0.5, 6.0);
    glRotated(20+36, 0.0, 0.0 ,1.0);
    drawStar();
    glPopMatrix();
}

