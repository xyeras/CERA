#include "enms2.h"
textureLoader attack[10];

enms2::enms2()
{
    //ctor
    xPos =0.0;             //placing objects on x
    yPos =0.0;             //placing objects on y
    zPos = -5.0;             //placing objects on z
    EnemyLife = 3;
    xSize = 1.0;            // for scaling x
    ySize = 0.5;            // for scaling y

    rotateX =0.0;
    rotateY =0.0;
    rotateZ =0.0;

    frames = 10;
    xmin=0;
    ymin=0;
    xmax = 1.0/frames;
    ymax = 1.0/frames;
    xmove=0.01;
    ymove=0.01;
    action=0;
    arrowLoc.x=0;
    arrowLoc.y=0;
}

enms2::~enms2()
{
    //dtor
}
void enms2::initAttack(int s)
{
//    TE->start();
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//
//    attack[0].bindTexture("images/Demon attacks/DA1.png");
//    attack[1].bindTexture("images/Demon attacks/DA2.png");
//    attack[2].bindTexture("images/Demon attacks/DA3.png");
//    attack[3].bindTexture("images/Demon attacks/DA4.png");
//    attack[4].bindTexture("images/Demon attacks/DA5.png");
//    attack[5].bindTexture("images/Demon attacks/DA6.png");
//    attack[6].bindTexture("images/Demon attacks/DA7.png");
//    attack[7].bindTexture("images/Demon attacks/DA8.png");
//    attack[8].bindTexture("images/Demon attacks/DA9.png");
//    attack[9].bindTexture("images/Demon attacks/DA10.png");
//    arrowLoc.sizes = s;
//    arrTex = tex
}

void enms2::drawAttack()
{


    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,arrTex);
    glPushMatrix();
    glTranslatef(arrowLoc.x ,arrowLoc.y,zPos);
    glRotated(180,0,0,1);

    glScaled(0.25,0.25,1);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);

        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);
     glEnd();
     glPopMatrix();
}

void enms2::drawEnemy()
{
     if(isEnemyLive)          // check status
    {
      glColor3f(1.0,1.0,1.0); // set initial color
      glBindTexture(GL_TEXTURE_2D, EnemyTex); // bind texture

      glPushMatrix();
       glTranslatef(xPos,yPos,zPos);   // position of the object
       glRotatef(rotateX,1.0,0.0,0.0); // rotate around x axis
       glRotatef(rotateY,0.0,1.0,0.0); // rotate around y axis
       glRotatef(rotateZ,0.0,0.0,1.0); // rotate around z axis
       glScalef(xSize,ySize,1);        // scale object

       glBegin(GL_POLYGON);

          glTexCoord2f(xmin,ymin);
          glVertex3f(1.0,1.0,0.0);

          glTexCoord2f(xmax,ymin);
          glVertex3f(-1.0,1.0,0.0);

          glTexCoord2f(xmax,ymax);
          glVertex3f(-1.0,-1.0,0.0);

          glTexCoord2f(xmin,ymax);
          glVertex3f(1.0,-1.0,0.0);

       glEnd();
      glPopMatrix();
    }
}

void enms2::placeEnemy(float x, float y, float z)
{
    xPos =x;   // placing x
    yPos =y;   // placing y
    zPos =z;   // placing z
    TE->start();
}

void enms2::actions()
{
   switch(action){
   case 0:
       if(TE->getTicks()>200){
            xmin+= 1.0/frames;
            xmax+= 1.0/frames;
            ymin = 0.5;
            ymax = 1.0;
            //arrowLoc.x-=0.01;
            if(xmax>=3){xmin=0; xmax =1.0/frames;}
         TE->reset();
          }
          //drawAttack();
          drawEnemy();

       break;

   case 1:

   if(TE->getTicks()>200){

            xmin += 1.0/frames;
            xmax += 1.0/frames;
            ymin = 0.0;
            ymax = 0.5;
            //arrowLoc.x-=0.01;
            if(xmax>=3){xmin=0; xmax =1.0/frames;}
        TE->reset();
   }
   //drawAttack();
      drawEnemy();

     break;
   }
}
