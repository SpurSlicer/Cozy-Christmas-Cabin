#include "window.h"
// MAYBE CHANGE SO CLIPPING ISNT NOTICABLE
void Window::drawWindow() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    for (double j = -2.2; j <= 2.2; j += 2.2) {
        for (double i = 12.4; i <= 12.6; i += 0.2) {
            glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 1.0);
            glNormal3f(0.0, 0.0, 1.0); // PLUS_Z;
            glVertex3d(24.9, 4.25, i+j);
            glVertex3d(25.1, 4.25, i+j);
            glVertex3d(25.1, 7.75, i+j);
            glVertex3d(24.9, 7.75, i+j);
            glEnd();
        }
        for (double i = 24.9; i <= 25.1; i += 0.2) {
            glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 1.0);
            glNormal3f(-1.0, 0.0, 0.0); // MINUS_X;
            glVertex3d(i, 4.25, 12.4+j);
            glVertex3d(i, 4.25, 12.6+j);
            glVertex3d(i, 7.75, 12.6+j);
            glVertex3d(i, 7.75, 12.4+j);
            glEnd();
        }
    }
    for (double i = 0.0; i <= 3.3; i += 1.65) {
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glNormal3f(0.0, -1.0, 0.0); // MINUS_Y;
        glVertex3d(24.9, 4.25+i, 10.2);
        glVertex3d(25.1, 4.25+i, 10.2);
        glVertex3d(25.1, 4.25+i, 14.8);
        glVertex3d(24.9, 4.25+i, 14.8);
        glEnd();
    }
    for (double j = 0; j <= 3.3; j += 1.65) {
        for (double i = 24.9; i <= 25.1; i += 0.2) {
            glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 1.0);
            glNormal3f(-1.0, 0.0, 0.0); // MINUS_X;
            glVertex3d(i, 4.25+j, 10.4);
            glVertex3d(i, 4.25+j, 14.6);
            glVertex3d(i, 4.45+j, 14.6);
            glVertex3d(i, 4.45+j, 10.4);
            glEnd();
        }
    }
}

void Window::drawWindowTop() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    for (double j = 0; j <= 0.2; j += 0.2) {
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        if (j == 0) glNormal3f(-1.0, 0.0, 0.0); // MINUS_X;
        else glNormal3f(1.0, 0.0, 0.0); // PLUS_X;
        glVertex3d(24.9+j, 7.55, 10.2);
        glVertex3d(24.9+j, 7.55, 14.8);
        glVertex3d(24.9+j, 7.75, 14.8);
        glVertex3d(24.9+j, 7.75, 10.2);
        glEnd();
    }
    for (double j = 0; j <= 0.2; j += 0.2) {
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        if (j == 0) glNormal3f(0.0, -1.0, 0.0); // MINUS_Y;
        else glNormal3f(0.0, 1.0, 0.0); // PLUS_Y;
        glVertex3d(24.9, 7.55+j, 10.2);
        glVertex3d(24.9, 7.55+j, 14.8);
        glVertex3d(25.1, 7.55+j, 14.8);
        glVertex3d(25.1, 7.55+j, 10.2);
        glEnd();
    }
}

void Window::drawLeft() {
    (this->state) ? (drawWindowTop()) : (drawWindow());
}

void Window::drawRight() {
    glPushMatrix();
    glTranslated(-25.0, 0.0, 0.0);
    (this->state) ? (drawWindowTop()) : (drawWindow());
    glPopMatrix();
}

void Window::toggleState() {
    this->state = !this->state;
};