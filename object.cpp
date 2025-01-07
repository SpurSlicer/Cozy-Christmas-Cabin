#include "object.h"
#include <GL/glut.h>


coordinate* Object::generateNormalByTriangle(coordinate* c1, coordinate* c2, coordinate* c3) {
    coordinate* cross_product = new coordinate({0, 0, 0});
    //printf("AVERAGE - x: %f, y: %f, z: %f of size %d\n", vector->x, vector->y, vector->z, size);
    coordinate* vector_u = new coordinate({c2->x-c1->x, c2->y-c1->y, c2->z-c1->z});
    coordinate* vector_v = new coordinate({c3->x-c1->x, c3->y-c1->y, c3->z-c1->z});
    cross_product->x = vector_u->y*vector_v->z - vector_u->z*vector_v->y;
    cross_product->y = vector_u->z*vector_v->x - vector_u->x*vector_v->z;
    cross_product->z = vector_u->x*vector_v->y - vector_u->y*vector_v->x;
    //printf("NORMAL - x: %f, y: %f, z: %f\n", cross_product->x, cross_product->y, cross_product->z);
    // glNormal3f(cross_product->x, cross_product->y, cross_product->z);
    delete vector_u;
    delete vector_v;
    return cross_product;
}
coordinate* Object::generateNormalByTriangleFLIP(coordinate* c1, coordinate* c2, coordinate* c3) {
    coordinate* cross_product = new coordinate({0, 0, 0});
    //printf("AVERAGE - x: %f, y: %f, z: %f of size %d\n", vector->x, vector->y, vector->z, size);
    coordinate* vector_u = new coordinate({c2->x-c1->x, c2->y-c1->y, c2->z-c1->z});
    coordinate* vector_v = new coordinate({c3->x-c1->x, c3->y-c1->y, c3->z-c1->z});
    cross_product->x = -(vector_u->y*vector_v->z - vector_u->z*vector_v->y);
    cross_product->y = -(vector_u->z*vector_v->x - vector_u->x*vector_v->z);
    cross_product->z = -(vector_u->x*vector_v->y - vector_u->y*vector_v->x);
    //printf("NORMAL - x: %f, y: %f, z: %f\n", cross_product->x, cross_product->y, cross_product->z);
    // glNormal3f(-cross_product->x, -cross_product->y, -cross_product->z);
    delete vector_u;
    delete vector_v;
    return cross_product;
}
coordinate* Object::generateNormalBySquare(coordinate* c1, coordinate* c2, coordinate* c3, coordinate* c4) {
    coordinate* cross_product = new coordinate({0, 0, 0});
    coordinate* vector_u = new coordinate({c3->x-c1->x, c3->y-c1->y, c3->z-c1->z});
    coordinate* vector_v = new coordinate({c4->x-c2->x, c4->y-c2->y, c4->z-c2->z});
    //printf("AVERAGE - x: %f, y: %f, z: %f of size %d\n", vector->x, vector->y, vector->z, size);
        cross_product->x = vector_u->y*vector_v->z - vector_u->z*vector_v->y;
        cross_product->y = vector_u->z*vector_v->x - vector_u->x*vector_v->z;
        cross_product->z = vector_u->x*vector_v->y - vector_u->y*vector_v->x;
    //printf("NORMAL - x: %f, y: %f, z: %f\n", cross_product->x, cross_product->y, cross_product->z);
    // glNormal3f(cross_product->x, cross_product->y, cross_product->z);
    delete vector_u;
    delete vector_v;
    return cross_product;
}
coordinate* Object::generateNormalBySquareFLIP(coordinate* c1, coordinate* c2, coordinate* c3, coordinate* c4) {
    coordinate* cross_product = new coordinate({0, 0, 0});
    coordinate* vector_u = new coordinate({c3->x-c1->x, c3->y-c1->y, c3->z-c1->z});
    coordinate* vector_v = new coordinate({c4->x-c2->x, c4->y-c2->y, c4->z-c2->z});
    //printf("AVERAGE - x: %f, y: %f, z: %f of size %d\n", vector->x, vector->y, vector->z, size);
    cross_product->x = -(vector_u->y*vector_v->z - vector_u->z*vector_v->y);
    cross_product->y = -(vector_u->z*vector_v->x - vector_u->x*vector_v->z);
    cross_product->z = -(vector_u->x*vector_v->y - vector_u->y*vector_v->x);
    //printf("NORMAL - x: %f, y: %f, z: %f\n", cross_product->x, cross_product->y, cross_product->z);
    // glNormal3f(-cross_product->x, -cross_product->y, -cross_product->z);
    delete vector_u;
    delete vector_v;
    return cross_product;
}

char* ReadText(char *file)
{
   char* buffer;
   //  Open file
   FILE* f = fopen(file,"rt");
   if (!f) {
        printf("Cannot open text file %s\n",file);
        exit(-1);
   }
   //  Seek to end to determine size, then rewind
   fseek(f,0,SEEK_END);
   int n = ftell(f);
   rewind(f);
   //  Allocate memory for the whole file
   buffer = (char*)malloc(n+1);
   if (!buffer) {
    printf("Cannot allocate %d bytes for text file %s\n",n+1,file);
    exit(-1);
   }
   //  Snarf the file
   if (fread(buffer,n,1,f)!=1) {
    printf("Cannot read %d bytes for text file %s\n",n,file);
    exit(-1);
   }
   buffer[n] = 0;
   //  Close and return
   fclose(f);
   return buffer;
}

/*
 *  Print Shader Log
 */
void PrintShaderLog(int obj,char* file)
{
   int len=0;
   glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) {
        printf("Cannot allocate %d bytes of text for shader log\n",len);
        exit(-1);
      }
      glGetShaderInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s:\n%s\n",file,buffer);
      free(buffer);
   }
   glGetShaderiv(obj,GL_COMPILE_STATUS,&len);
   if (!len) {
    printf("Error compiling %s\n",file);
    exit(-1);
   }
}

/*
 *  Print Program Log
 */
void PrintProgramLog(int obj)
{
   int len=0;
   glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) {
        printf("Cannot allocate %d bytes of text for program log\n",len);
        exit(-1);
      }
      glGetProgramInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s\n",buffer);
   }
   glGetProgramiv(obj,GL_LINK_STATUS,&len);
   if (!len) {
        printf("Error linking program\n");
        exit(-1);
   }
}


int CreateShader(GLenum type,char* file)
{
   //  Create the shader
   int shader = glCreateShader(type);
   //  Load source code from file
   char* source = ReadText(file);
   glShaderSource(shader,1,(const char**)&source,NULL);
   free(source);
   //  Compile the shader
   fprintf(stderr,"Compile %s\n",file);
   glCompileShader(shader);
   //  Check for errors
   PrintShaderLog(shader,file);
   //  Return name
   return shader;
}


void Object::generateShader(std::string name, std::string vert_name, std::string frag_name) {
    int prog = glCreateProgram();
    int vert = CreateShader(GL_VERTEX_SHADER, (char*)vert_name.c_str());
    int frag = CreateShader(GL_FRAGMENT_SHADER, (char*)frag_name.c_str());
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    PrintProgramLog(prog);
    this->shaders[name] = prog;
}

void Object::enableShader(std::string shader) {
    glUseProgram(this->shaders[shader]);
    int id = glGetUniformLocation(this->shaders[shader],"u_time");
    glUniform1f(id, 0.001 * glutGet(GLUT_ELAPSED_TIME));
    
}
void Object::enableShaderWTick(std::string shader) {
    glUseProgram(this->shaders[shader]);
    int id = glGetUniformLocation(this->shaders[shader],"u_time");
    glUniform1f(id, this->tick);
}
void Object::setVec3(std::string shader_name, std::string name, double x, double y, double z) {
    int id = glGetUniformLocation(this->shaders[shader_name], name.c_str());
    glUniform3f(id ,x, y, z);
}

void Object::disableShader() {
    glUseProgram(0);
}


void Reverse(void* x,const int n)
{
   char* ch = (char*)x;
   for (int k=0;k<n/2;k++)
   {
      char tmp = ch[k];
      ch[k] = ch[n-1-k];
      ch[n-1-k] = tmp;
   }
}
/*
USED FROM http://tfc.duke.free.fr/coding/src/png.c
*/
void GetPNGtextureInfo (int color_type, struct gl_texture_t *texinfo)
{
  switch (color_type)
    {
    case PNG_COLOR_TYPE_GRAY:
      texinfo->format = GL_LUMINANCE;
      texinfo->internalFormat = 1;
      break;

    case PNG_COLOR_TYPE_GRAY_ALPHA:
      texinfo->format = GL_LUMINANCE_ALPHA;
      texinfo->internalFormat = 2;
      break;

    case PNG_COLOR_TYPE_RGB:
      texinfo->format = GL_RGB;
      texinfo->internalFormat = 3;
      break;

    case PNG_COLOR_TYPE_RGB_ALPHA:
      texinfo->format = GL_RGBA;
      texinfo->internalFormat = 4;
      break;

    default:
      /* Badness */
      break;
    }
}

struct gl_texture_t* generateTextureInfo(std::string tex_name_str)
{
    char* tex_name = (char*)tex_name_str.c_str();
    struct gl_texture_t* tex_info = (struct gl_texture_t*)malloc(sizeof(struct gl_texture_t));
    FILE* f = fopen(tex_name,"rb");
    if (!f) { perror("Cannot open file\n"); exit(-1); }
    png_byte magic[8];
    if (fread(magic,sizeof(magic),1,f)!=1) { perror("Cannot read magic\n"); exit(-1); }
    if (!png_check_sig(magic, sizeof(magic))) {
        fprintf(stderr, "error: %s couldn't open!\n", tex_name);
        exit(-1);
    }
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        perror("Couldn't assemble png struct\n");
        fclose(f);
        exit(-1);
    }
    png_infop info_ptr = png_create_info_struct (png_ptr);
    if (!info_ptr)
    {
        fclose (f);
        png_destroy_read_struct (&png_ptr, nullptr, nullptr);
        exit(-1);
    }
    if (setjmp(png_jmpbuf(png_ptr))) {
        fclose(f);
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        perror("Couldn't do the setjmp stuff\n");
        exit(-1);
    }
    png_init_io (png_ptr, f);
    png_set_sig_bytes (png_ptr, sizeof (magic));
    png_read_info (png_ptr, info_ptr);
    int bit_depth = png_get_bit_depth (png_ptr, info_ptr);
    int color_type = png_get_color_type (png_ptr, info_ptr);
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb (png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid (png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha (png_ptr);
    if (bit_depth == 16)
        png_set_strip_16 (png_ptr);
    else if (bit_depth < 8)
        png_set_packing (png_ptr);
    png_read_update_info (png_ptr, info_ptr);
    png_uint_32 w;
    png_uint_32 h;
    png_get_IHDR (png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, NULL, NULL, NULL);
    tex_info->width = w;
    tex_info->height = h;
    GetPNGtextureInfo (color_type, tex_info);
    tex_info->texels = (GLubyte *)malloc (sizeof (GLubyte) * tex_info->width * tex_info->height * tex_info->internalFormat);
    png_bytep* row_pointers = (png_bytep *)malloc (sizeof (png_bytep) * tex_info->height);
    int i;
    for (i = 0; i < tex_info->height; ++i) {
        #if 1
            row_pointers[i] = (png_bytep)(tex_info->texels +
            ((tex_info->height - (i + 1)) * tex_info->width * tex_info->internalFormat));
        #else
            row_pointers[i] = (png_bytep)(tex_info->texels +
            (tex_info->width * i * tex_info->internalFormat));
        #endif
    }
    png_read_image (png_ptr, row_pointers);
    png_read_end (png_ptr, NULL);
    png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
    free (row_pointers);
    fclose (f);
    return tex_info;
}

void Object::generateTexture(std::string name, std::string file_name) {
    struct gl_texture_t* png_tex = generateTextureInfo(file_name.c_str());
    GLint alignment;
    if (png_tex && png_tex->texels)
    {
        /* Generate texture */
        glGenTextures (1, &png_tex->id);
        glBindTexture (GL_TEXTURE_2D, png_tex->id);

        /* Setup some parameters for texture filters and mipmapping */
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGetIntegerv (GL_UNPACK_ALIGNMENT, &alignment);
        glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D (GL_TEXTURE_2D, 0, png_tex->internalFormat,
            png_tex->width, png_tex->height, 0, png_tex->format,
            GL_UNSIGNED_BYTE, png_tex->texels);
        gluBuild2DMipmaps (GL_TEXTURE_2D, png_tex->internalFormat,
                png_tex->width, png_tex->height,
                png_tex->format, GL_UNSIGNED_BYTE, png_tex->texels);

        glPixelStorei (GL_UNPACK_ALIGNMENT, alignment);

        this->textures[name] = png_tex->id;

        /* OpenGL has its own copy of texture data */
        free(png_tex->texels);
        free(png_tex);
    } else {
        fprintf(stderr, "Texture %s was NOT loaded!\n", file_name.c_str());
    }
}
/*
END OF USED SECTION
*/

void Object::generateTexture(std::string name, int index) {
    this->textures.insert_or_assign(name, index);
}
void Object::generateShader(std::string name, int index) {
    this->shaders.insert_or_assign(name, index);
}
void Object::applyTexture(std::string name) {
    glBindTexture(GL_TEXTURE_2D, this->textures[name]);
}
void Object::applyTexture(std::string name, int id) {
    glActiveTexture(GL_TEXTURE0+id);
    glBindTexture(GL_TEXTURE_2D, this->textures[name]);
}

void Object::enableTextures() {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Object::disableTextures() {
    glDisable(GL_TEXTURE_2D);
}

// BASE RETRIEVED FROM: https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// NOTE: THIS WAS MODIFIED HEAVILYYY LIKE 80% OF IT IS DIFFERENT!!
void Object::generateModel(std::string name, std::string file_name) {
    Model* model = new Model();
    FILE* f = fopen(file_name.c_str(), "r");
    if (!f) {
        printf("[ERROR]: Could not open model file %s\n", file_name.c_str());
        exit(-1);
    }
    char* line = (char*)calloc(256, sizeof(char));
    char* useless = (char*)calloc(256, sizeof(char));
    while (!feof(f)) {
        std::memset(line, 0, 256);
        fgets(line, 256, f);
        //int res = fscanf(f, "%s\n", line);
        if (std::strncmp(line, "vt", 2) == 0) {
            coordinate* coord = new coordinate();
            sscanf(line, "%s%le %le\n", useless, &coord->x, &coord->y);
            coord->z = 0.0;
            model->uvs.push_back(coord);
        } else if (std::strncmp(line, "vn", 2) == 0) {
            coordinate* coord = new coordinate();
            sscanf(line, "%s%le %le %le\n", useless, &coord->x, &coord->y, &coord->z);
            model->normals.push_back(coord);
        } else if (std::strncmp(line, "v", 1) == 0) {
            coordinate* coord = new coordinate();
            sscanf(line, "%s%le %le %le\n", useless, &coord->x, &coord->y, &coord->z);
            model->vertices.push_back(coord);
        } else if (strncmp(line, "f", 1) == 0) {
            std::vector<coordinate*> coords;
            std::string scan_str = "%s";
            for (int i = 0; i < MAX_VERTICES; i++) {
                coords.push_back(new coordinate());
                if (i+1 == MAX_VERTICES) scan_str += "%le/%le/%le\n";
                else scan_str += "%le/%le/%le ";
            }
            int read_size = sscanf(line, scan_str.c_str(), useless, 
                &coords[0]->x, &coords[0]->y, &coords[0]->z,
                &coords[1]->x, &coords[1]->y, &coords[1]->z,
                &coords[2]->x, &coords[2]->y, &coords[2]->z,
                &coords[3]->x, &coords[3]->y, &coords[3]->z,
                &coords[4]->x, &coords[4]->y, &coords[4]->z,
                &coords[5]->x, &coords[5]->y, &coords[5]->z,
                &coords[6]->x, &coords[6]->y, &coords[6]->z,
                &coords[7]->x, &coords[7]->y, &coords[7]->z,
                &coords[8]->x, &coords[8]->y, &coords[8]->z,
                &coords[9]->x, &coords[9]->y, &coords[9]->z,
                &coords[10]->x, &coords[10]->y, &coords[10]->z,
                &coords[11]->x, &coords[11]->y, &coords[11]->z,
                &coords[12]->x, &coords[12]->y, &coords[12]->z,
                &coords[13]->x, &coords[13]->y, &coords[13]->z,
                &coords[14]->x, &coords[14]->y, &coords[14]->z,
                &coords[MAX_VERTICES-1]->x, &coords[MAX_VERTICES-1]->y, &coords[MAX_VERTICES-1]->z);
            if (read_size == 0) {
                printf("[ERROR] Read 0 indices for %s", line);
                exit(-1);
            }
            int i = 0;
            for (; i < read_size/3; i++) {
                model->indices.push_back(coords[i]);
            }
            for (; i < MAX_VERTICES; i++) {
                delete coords[i];
            }
            model->batch.push_back(read_size/3);
        } else if (strncmp(line, "usemtl", 6) == 0) {
            char mtl[256];
            sscanf(line, "usemtl %s\n", mtl);
            std::string new_mtl = mtl;
            //printf("%s\tNew MTL: %s\n\tOld MTL: %s\n", line, new_mtl.c_str(), mtl);
            model->texs.push_back(std::make_pair(model->batch.size(), new_mtl));
        } else {
            //printf("Wonky thing entered\n");
        }
    }
    //printf("vert: %d; uv: %d; norm: %d; in: %d; batch: %d texs: %d\n", model->vertices.size(), model->uvs.size(), model->normals.size(), model->indices.size(), model->batch.size(), model->texs.size());
    fclose(f);
    free(line);
    this->models[name] = model;
}

Model* Object::getModel(std::string name) { return this->models[name]; }
void Object::applyTexForModel(std::string model_name, int batch) {
    Model* model = this->models[model_name];
    for (int i = 0; i < (int)model->texs.size(); i++) {
        if (batch <= model->texs[i].first) {
            this->applyTexture(model->texs[i].second);
            return;
        }
    }
    return;
}

void Object::updateTick() {
    this->tick += 0.01;
    if (this->tick == 1.0) this->tick -= 1;
}
