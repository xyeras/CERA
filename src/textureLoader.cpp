#include "textureLoader.h"
#include <iostream>
using namespace std;
textureLoader::textureLoader()
{
    //ctor
}

textureLoader::~textureLoader()
{
    //dtor
}

void textureLoader::bindTexture(char* fileName)
{



    glEnable(GL_TEXTURE_2D);
 glGenTextures(1, &tex);
 glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
 glBindTexture(GL_TEXTURE_2D, tex); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
 int width, height; // width & height for the image reader
 unsigned char* image;
 image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);
 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// binding image data
 SOIL_free_image_data(image);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 /*   glGenTextures(1,&tex);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, tex);
    image = SOIL_load_image(fileName,&width,&height,0,SOIL_LOAD_RGB);

    if (!image)
        cout << "Failed to find image" << endl;

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    //SOIL_free_image_data(image);

    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);*/
}

void textureLoader::binder()
{
    glBindTexture(GL_TEXTURE_2D,tex);
}
