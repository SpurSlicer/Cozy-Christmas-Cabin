#include "camera.h"

void Camera::project() {
    glMatrixMode(GL_PROJECTION);
    //  Undo previous transformations
    glLoadIdentity();
    //  Perspective transformation
    gluPerspective(this->fov,this->asp,this->dim/16,16*this->dim); // zNear and zFar defines clipping distance and render distance, respectively
    //  Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
    //  Undo previous transformations
    glLoadIdentity();
}

void Camera::resetAngles() {
    this->th = 0;
    this->ph = 0;
}

void Camera::resetAnglesPerpendicular() {
    this->th = 0;
    this->ph = 0;
}

void Camera::reshapeAsp(int width, int height) {
    this->asp = (height>0) ? (double)width/height : 1;
}

void Camera::rotate(int x, int y) {
    if (!this->is_paused) {
        y = -y;
        if (this->ph + y < 91 && this->ph + y > -91) this->ph += y;
        if (this->th + x > 360) this->th += x - 360;
        else if (this->th + x < 0) this->th += x + 360;
        else this->th += x;
    }
}

void Camera::idleSetZh(double t) { // ?
    zh = fmod(90*t,360);
}

int Camera::getTh() { return this->th; }
int Camera::getPh() { return this->ph; }

void Camera::display() {
    glRotatef(this->ph, -1, 0, 0);
    gluLookAt(this->pos_x, this->pos_y, this->pos_z, (this->pos_x+Sin(this->th)), this->pos_y, (this->pos_z-Cos(th)) , 0,Cos(this->ph),0);
}

bool Camera::checkColission(float x, float y, float z) {
    if (x < 2.5 || x > 22.5) return true;
    if (z < 2.5 || z > 21.5) return true;
    if (x > 16.5 && z < 10) return true;
    if (x > 16.5 && z > 15) return true;
    if (z < 5.0 && x < 9.5) return true;
    return false;
}

void Camera::move() {
    if (!this->is_paused) {
        if (this->movement.RIGHT) {
            float new_x = this->pos_x + Cos(th)*0.35;
            float new_z = this->pos_z + Sin(th)*0.35;
            if (this->checkColission(new_x, 0, new_z)) return;
            this->pos_x = new_x;
            this->pos_z = new_z;
        }
        if (this->movement.UP) {
            float new_x = this->pos_x + Sin(th)*0.35;
            float new_z = this->pos_z - Cos(th)*0.35;
            if (this->checkColission(new_x, 0, new_z)) return;
            this->pos_x = new_x;
            this->pos_z = new_z;
        }
        if (this->movement.LEFT) {
            float new_x = this->pos_x - Cos(th)*0.35;
            float new_z = this->pos_z - Sin(th)*0.35;
            if (this->checkColission(new_x, 0, new_z)) return;
            this->pos_x = new_x;
            this->pos_z = new_z;
        }
        if (this->movement.DOWN) {
            float new_x = this->pos_x - Sin(th)*0.35;
            float new_z = this->pos_z + Cos(th)*0.35;
            if (this->checkColission(new_x, 0, new_z)) return;
            this->pos_x = new_x;
            this->pos_z = new_z;
        }
    }
}

void Camera::toggleOn(MovementState state) { 
    switch (state) {
        case LEFT:
            this->movement.LEFT = true;
            break;
        case RIGHT:
            this->movement.RIGHT = true;
            break;
        case UP:
            this->movement.UP = true;
            break;
        case DOWN:
            this->movement.DOWN = true;
            break;
        default:
            printf("[ERROR] weird movement state used\n");
    }
}
void Camera::toggleOff(MovementState state) { 
    switch (state) {
        case LEFT:
            this->movement.LEFT = false;
            break;
        case RIGHT:
            this->movement.RIGHT = false;
            break;
        case UP:
            this->movement.UP = false;
            break;
        case DOWN:
            this->movement.DOWN = false;
            break;
        default:
            printf("[ERROR] weird movement state used\n");
    }
}

void Camera::togglePausedState() {
    this->is_paused = !this->is_paused;
}