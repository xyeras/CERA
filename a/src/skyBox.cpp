#include "skyBox.h"
#include <iostream>
using namespace std;

 textureLoader tLoad[6];

skyBox::skyBox()
{
    //ctor

    RotateX =0;
    RotateY =0;
    RotateZ =0;

    translateX =0;
    translateY =0;
    translateZ =0;
}

skyBox::~skyBox()
{
    //dtor
}
void skyBox::loadTextures()
{

   glEnable(GL_TEXTURE_2D);
 //  glGenTextures(6,tex);
   tLoad[0].bindTexture("images/Box/front.jpg");
   tLoad[1].bindTexture("images/Box/back.jpg");
   tLoad[2].bindTexture("images/Box/top.jpg");
   tLoad[3].bindTexture("images/Box/bottom.jpg");
   tLoad[4].bindTexture("images/Box/left.jpg");
   tLoad[5].bindTexture("images/Box/right.jpg");
}

void skyBox::drawBox()
{
    //Front Face



    glRotated(RotateX,1,0,0);
    glRotated(RotateY,0,1,0);
    glRotated(RotateZ,0,0,1);

 // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
    tLoad[0].binder();
    glBegin(GL_QUADS);
   // Front Face  Y
  //  glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();

    tLoad[1].binder(); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
    glBegin(GL_QUADS);
  // Back Face Y
  //  glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glEnd();

    tLoad[2].binder();// images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
    glBegin(GL_QUADS);

    // Top Face  X
 //  glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glEnd();

    tLoad[3].binder(); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
    glBegin(GL_QUADS);
    // Bottom Face  Z
  //  glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.0f, -1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(  1.0f, -1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(  1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad

    glEnd();

    tLoad[4].binder(); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
    glBegin(GL_QUADS);
    // Right face  Y
 //   glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad

    glEnd();

    tLoad[5].binder(); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
    glBegin(GL_QUADS);
     // Left Face  Y
   // glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad

    glEnd();
}
