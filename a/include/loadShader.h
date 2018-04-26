#ifndef LOADSHADER_H
#define LOADSHADER_H

#define GLEW_STATIC
#include <GL/glew.h>


#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <fstream>

using namespace std;

class loadShader
{
    public:
        loadShader();
        virtual ~loadShader();
        void loadFile(char *,string&);
        unsigned vs, fs, program;
        unsigned int LoadShader(string&, unsigned int);
        void initShader(char *, char *);
        void cleanUp();

    protected:

    private:
};

#endif // LOADSHADER_H
