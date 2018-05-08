#include "loadShader.h"
#include <fstream>
loadShader::loadShader()
{
    //ctor
}

loadShader::~loadShader()
{
    //dtor
}
void loadShader::loadFile(char* FileName, string& str)
{
    char tmp[1024];
    ifstream in(FileName);
    if(!in.is_open())
    {
        cout<<"file not found"<<endl;
        return;
    }
    while(!in.eof())
    {
        in.getline(tmp,1024);
        str+=tmp;
        str+='\n';
    }
    //for debug
    cout<<str<<endl;
}
unsigned int loadShader::LoadShader(string& source, unsigned int mode)
{
    unsigned int id;
    const char* csource;
    char error[1024];
    csource = source.c_str();
    id=glCreateShader(mode);
    glShaderSource(id,1,&csource,NULL);
    glCompileShader(id);
    glGetShaderInfoLog(id,1024,NULL,error);

    cout<<"Compile Status: "<<error<<endl;
    return id;
}


void loadShader::shaderInit(char* vFileName, char* fFileName)
{
    string source;
    loadFile(vFileName,source);
    vs=LoadShader(source,GL_VERTEX_SHADER);
    source="";
    loadFile(fFileName,source);
    fs=LoadShader(source,GL_FRAGMENT_SHADER);
    source = "";

    program= glCreateProgram();
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
}

void loadShader::cleanUp()
{
    glDetachShader(program,vs);
    glDetachShader(program,fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(program);
}
