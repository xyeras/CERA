#include "Objects.h"

Objects::Objects()
{
    //ctor

    xPos = 0.0;                 // placing objects on x
    yPos = 0.0;                 // placing objects on y
    zPos = -5.0;                 // placing objects on z

    xSize = -5.0;                // for scaling x
    ySize = -5.0;                // for scaling y

    rotateX = 0.0;
    rotateY = 0.0;
    rotateZ = 0.0;
}

Objects::~Objects()
{
    //dtor
}

void Objects::drawObjects()
{
    if (isObjectLive)           // check status
    {
        glColor3f(1.0,1.0,1.0);  // set initial color
        glBindTexture(GL_TEXTURE_2D, objectTex);    // bind texture

        glPushMatrix();
            glTranslatef(xPos,yPos,zPos);          // position of the object
            glRotatef(rotateX,1.0,0.0,0.0);        //rotate around x axis
            glRotatef(rotateY,0.0,1.0,0.0);        // rotate around y axis
            glRotatef(rotateZ,0.0,0.0,1.0);        // rotate around z axis
            glScalef(xSize,ySize,1);               // scale object

            glBegin(GL_POLYGON);
                glTexCoord2f(0.0,0.0);
                glVertex3f(1.0,1.0,0.0);

                glTexCoord2f(1.0,0.0);
                glVertex3f(-1.0,1.0,0.0);

                glTexCoord2f(1.0,1.0);
                glVertex3f(-1.0,-1.0,0.0);

                glTexCoord2f(0.0,1.0);
                glVertex3f(1.0,-1.0,0.0);
            glEnd();
        glPopMatrix();
    }
}

void Objects::placeObjects(float x, float y, float z)
{
    xPos = x;       // placing x
    yPos = y;       // placing y
    zPos = z;       // placing z
}

