#include "Model.h"
#include <textureLoader.h>

textureLoader *tex = new textureLoader();


Model::Model()
{
    //ctor
    double RotateX = 0.0;   // rotations
    double RotateY = 0.0;
    double RotateZ = 0.0;

    double Zoom = -4.0;     //translations
    double Xpos = -0.5;
    double Ypos = -0.5;

    verticies[0].x = 0.0;
    verticies[0].y = 0.0;
    verticies[0].z = 1.0;

    verticies[1].x = 1.0;
    verticies[1].y = 0.0;
    verticies[1].z = 1.0;

    verticies[2].x = 1.0;
    verticies[2].y = 1.0;
    verticies[2].z = 1.0;

    verticies[3].x = 0.0;
    verticies[3].y = 1.0;
    verticies[3].z = 1.0;


}

Model::~Model()
{
    //dtor
}

void Model::modelInit(char * fileName, bool trans)
{
    if (trans == true)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    tex->binder();
    tex->bindTexture(fileName);
}


void Model::drawModel()
{
    glColor3f(0.8,0.5,0.0);
    tex->binder();
    glTranslated(Xpos,Ypos,Zoom);
    glRotated(RotateX,1,0,0);
    glRotated(RotateY,0,1,0);
    glRotated(RotateZ,0,0,1);

    glBegin(GL_QUADS);

    glVertex2d(0.0,1.0);
    glTexCoord2f(0.0,1.0);
    glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);

    glTexCoord2f(1.0,1.0);
    glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);

    glTexCoord2f(1.0,0.0);
    glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);

    glTexCoord2f(0.0,0.0);
    glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);


    glEnd();
}
