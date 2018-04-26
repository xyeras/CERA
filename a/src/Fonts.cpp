#include "Fonts.h"
#include <textureLoader.h>

textureLoader *fTex = new textureLoader();

Fonts::Fonts()
{
    //ctor

    zoom =-4.0;
    xpos = 1.5;
    ypos =0.0;
    zpos =0.0;
    cCnt =0;
}

Fonts::~Fonts()
{
    //dtor
}

void Fonts::initFonts(char* fileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    fTex ->binder();
    fTex->bindTexture(fileName);
}

void Fonts::buildFont(char* str)
{
    for(int i=0;i<strlen(str);i++)
    {
        switch (str[i]){
        case 'a':
              C[cCnt].xmin = 0;
              C[cCnt].xmax = 1.0/13.0;
             // C[cCnt].ymin = ???
             // C[cCnt].ymax = ???

        break;

        case 'A':
              C[cCnt].xmin = 0;
              C[cCnt].xmax = 1.0/13.0;
             // C[cCnt].ymin = ???
             // C[cCnt].ymax = ???
            break;



        }
        cCnt++;
    }
}

void Fonts::drawFont(int i)
{
    fTex->binder();

    glPushMatrix();
    glBegin(GL_QUADS);

    glTexCoord2f(C[i].xmin,1.0);   // fix your y vales
    glVertex3f(0,0,0);

    glTexCoord2f(C[i].xmax,1.0);
    glVertex3f(1.0/13.0,0,0);

    glTexCoord2f(C[i].xmax,0.0);
    glVertex3f(1.0/13.0,1,0);

    glTexCoord2f(C[i].xmin,0.0);
    glVertex3f(0,1,0);

    glEnd();
    glPopMatrix();

}
