#include "models.h"

ArmChair::ArmChair() {
    //this->generateShader("phong", "pixlight.vert", "pixlight.frag");
    this->generateModel("armchair", "_armchair2.obj");
    this->generateTexture("bronze", "_bronze.png");
    this->generateTexture("chair", "_chair.png");
    this->generateTexture("leather", "_leather.png");
}

void ArmChair::draw() {
    const std::string model_name = "armchair";
    const Model* model = this->models[model_name];
    const int size = model->batch.size();
    //printf("MODEL STUFF: i: %d; v: %d; uv: %d; n: %d\n", model->indices.size(), model->vertices.size(), model->uvs.size(), model->normals.size());
    glPushMatrix();
    glTranslated(21.0, 0.0, 19.0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glRotated(-55.0, 0.0, 0.0, 1.0);
    glScaled(0.055, 0.055, 0.055);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);    
    int base_i = 0;
    for (int i = 0; i < size; i++) {
        int j = 0;
        this->applyTexForModel(model_name, i);
        glBegin(GL_POLYGON);
        // this->setColor(1.0, 1.0, 1.0);
        glColor3f(1.0, 1.0, 1.0);
        for (; j < model->batch[i]; j++) {
            // if (j > 4) printf("BIGGIE!%d\n", j);
            glNormal3f(model->normals[model->indices[base_i+j]->z-1]->x,
                       model->normals[model->indices[base_i+j]->z-1]->y,
                       model->normals[model->indices[base_i+j]->z-1]->z);
            glTexCoord2f(model->uvs[model->indices[base_i+j]->y-1]->x,
                         model->uvs[model->indices[base_i+j]->y-1]->y);
            glVertex3f(model->vertices[model->indices[base_i+j]->x-1]->x,
                       model->vertices[model->indices[base_i+j]->x-1]->y,
                       model->vertices[model->indices[base_i+j]->x-1]->z);
        }
        glEnd();
        base_i += j;
    }
    this->disableTextures();
    glPopMatrix();
}

void Bookshelf::draw() {
    const std::string model_name = "bookshelf";
    const Model* model = this->models[model_name];
    const int size = model->batch.size();
    //printf("MODEL STUFF: i: %d; v: %d; uv: %d; n: %d\n", model->indices.size(), model->vertices.size(), model->uvs.size(), model->normals.size());
    glPushMatrix();
    glTranslated(5.0, 0.0, 2.1);
    glScaled(0.025, 0.025, 0.025);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->lighting.shininess);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    this->enableTextures();
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);   
    int base_i = 0;
    for (int i = 0; i < size; i++) {
        int j = 0;
        this->applyTexForModel(model_name, i);
        glBegin(GL_POLYGON);
        glColor3f(0.322, 0.204, 0.106);
        for (; j < model->batch[i]; j++) {
            // if (j > 4) printf("BIGGIE!%d\n", j);
            glNormal3f(model->normals[model->indices[base_i+j]->z-1]->x,
                       model->normals[model->indices[base_i+j]->z-1]->y,
                       model->normals[model->indices[base_i+j]->z-1]->z);
            glTexCoord2f(model->uvs[model->indices[base_i+j]->y-1]->x,
                         model->uvs[model->indices[base_i+j]->y-1]->y);
            glVertex3f(model->vertices[model->indices[base_i+j]->x-1]->x,
                       model->vertices[model->indices[base_i+j]->x-1]->y,
                       model->vertices[model->indices[base_i+j]->x-1]->z);
        }
        glEnd();
        base_i += j;
    }
    this->disableTextures();
    glPopMatrix();
}


Bookshelf::Bookshelf() {
    this->generateModel("bookshelf", "_bookshelf.obj");
    this->generateTexture("books", "_books.png");
    //this->generateTexture("metalnessMap1", "metalnessMap1.png");
    //this->generateTexture("normalMap1", "normalMap1.png");
    this->generateTexture("wood_for_bookshelf", "_wood_for_bookshelf.png");
}

