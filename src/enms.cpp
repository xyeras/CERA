#include "enms.h"



enms::enms()
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

    frames = 6;
    xmin=0;
    ymin=0;
    xmax = 1.0/frames;
    ymax = 1.0/frames;
    xmove=0.01;
    ymove=0.01;
    action=0;
}

enms::~enms()
{
    //dtor
}

void enms::drawEnemy()
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
    }else
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

void enms::placeEnemy(float x, float y, float z)
{
    xPos =x;   // placing x
    yPos =y;   // placing y
    zPos =z;   // placing z
    TE->start();
}

void enms::actions()
{
   switch(action){
   case 0:
       if(TE->getTicks()>400){
            xmin+= 1.0/frames;
            xmax+= 1.0/frames;
            if(isEnemyLive)
            {
                ymin = 0.5;
                ymax = 1.0;
            }else
            {
                ymin = 0.0;
                ymax = 1.0;
            }


            if(xmax>=4&&isEnemyLive==true){xmin=0; xmax =1.0/frames;}
            else if(xmax>=4&&isEnemyLive==false){xmin=1;xmax=1;TE->stop();};

            TE->reset();
            //else TE->stop();
          }
          drawEnemy();
       break;

   case 1:

   if(TE->getTicks()>400){

            xmin += 1.0/frames;
            xmax += 1.0/frames;
            if(isEnemyLive)
            {
                ymin = 0.0;
                ymax = 0.5;
            }else
            {
                ymin = 0.0;
                ymax = 1.0;
            }


                if(xmax>=4&&isEnemyLive==true){xmin=0; xmax =1.0/frames;}
            else if(xmax>=4&&isEnemyLive==false){xmin=1;xmax=1;TE->stop();};
            TE->reset();
            //else TE->stop();
   }
      drawEnemy();
     break;
   }
}
