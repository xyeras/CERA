#ifndef LOADSHADER_H
#define LOADSHADER_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <string>
using namespace std;
class loadShader
{
    public:
        loadShader();
        virtual ~loadShader();
        void loadFile(char*,string&);
        unsigned int vs,fs,program;
        unsigned int LoadShader(string&,unsigned int);
        void shaderInit(char*,char*);
        void cleanUp();
    protected:

    private:
};

#endif // LOADSHADER_H
