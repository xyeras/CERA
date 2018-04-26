#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include<SOIL.h>
#include<gl/gl.h>

class textureLoader
{
    public:
        textureLoader();
        virtual ~textureLoader();
        void bindTexture(char *);
        void binder();
        unsigned char* image;
        int width, height;
        GLuint tex;
    protected:

    private:
};

#endif // TEXTURELOADER_H
