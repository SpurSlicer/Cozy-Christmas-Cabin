#include "snow_generator.h"

SnowFlake::SnowFlake(int shad_index, int tex_index) {
    this->x = (double)(1.0 / (std::rand() % (1000))) + (double)(std::rand() % 15);
    this->y = (double)(1.0 / (std::rand() % (1000))) + 15.0;
    this->z = (double)(1.0 / (std::rand() % (1000))) + (double)(std::rand() % 15);
    this->y_vel = 1.0 / (std::rand() % (10));
    this->generateShader(this->rem_white_name, shad_index);
    this->generateTexture(this->rem_white_name, tex_index);
    //this->generateTexture(this->rem_white_name, "_snowflake.png");
    //printf("%b\n", tex_index == this->textures[this->rem_white_name]);
    if (this->y_vel < 0.1) this->y_vel += 0.25;
    else if (this->y_vel > 0.6) this->y_vel -= 0.4;
    //printf("%f, %f, %f, %f\n", this->x, this->y, this->z, this->y_vel);
}
SnowFlake::~SnowFlake() {
    //delete this;
}
bool SnowFlake::deletable() { return this->y < 0; }

void SnowFlake::draw(bool flip) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableShader(this->rem_white_name);
    int id = glGetUniformLocation(this->shaders[this->rem_white_name],"v_min");
    glUniform4f(id, 0.40, 0.40, 0.40, 0.0);
    id = glGetUniformLocation(this->shaders[this->rem_white_name], "u_flag");
    glUniform1f(id, 0.0);
    this->enableTextures();
    this->applyTexture(this->rem_white_name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    if (flip) glNormal3f(-1.0, 0.0, 0.0); // MINUS_X
    else glNormal3f(1.0, 0.0, 0.0); // PLUS_X;
    glTexCoord2f(0.0, 0.0);
    glVertex3f(this->x, this->y, this->z);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(this->x, this->y+1.0, this->z);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(this->x, this->y+1.0, this->z+1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(this->x, this->y, this->z+1.0);
    glEnd();
    this->disableTextures();
    this->disableShader();
    this->y -= this->y_vel;
}

SnowGenerator::SnowGenerator() {
    this->generateShader(this->rem_white_name, "__snow.vert", "__snow.frag");
    this->generateTexture(this->rem_white_name, "_snowflake.png");
}
void SnowGenerator::createSnowFlake() {
    this->snowflakes.push_back(new SnowFlake(this->shaders[this->rem_white_name], this->textures[this->rem_white_name]));
}
void SnowGenerator::drawLeft() {
    glPushMatrix();
    glTranslated(25.0, 0.0, 5.0);
    std::vector<std::vector<SnowFlake*>::iterator> old_snowflakes;
    this->createSnowFlake();
    for (auto i = this->snowflakes.begin(); i != this->snowflakes.end(); i++) {
        if ((*i)->deletable()) {
            //printf("deletable");
            old_snowflakes.push_back(i);
        } else {
            (*i)->draw(false);
        }
    }
    for (auto i : old_snowflakes) {
        this->snowflakes.erase(i);
    }
    old_snowflakes.clear();
    glPopMatrix();
}
void SnowGenerator::drawRight() {
    glPushMatrix();
    glTranslated(-15.0, 0.0, 5.0);
    std::vector<std::vector<SnowFlake*>::iterator> old_snowflakes;
    this->createSnowFlake();
    for (auto i = this->snowflakes.begin(); i != this->snowflakes.end(); i++) {
        if ((*i)->deletable()) {
            old_snowflakes.push_back(i);
        } else {
            (*i)->draw(true);
        }
    }
    for (auto i : old_snowflakes) {
        this->snowflakes.erase(i);
    }
    old_snowflakes.clear();
    glPopMatrix();
}
