#include <player.h>
#include <timer.h>
#include <textureLoader.h>
#include <iostream>
using namespace std;
timer *T = new timer();
textureLoader runLeft[2];

textureLoader standLeft[2];
textureLoader standRight[2];
textureLoader standUp[2];
textureLoader standDown[2];

textureLoader attackLeft[2];
textureLoader attackRight[2];
textureLoader attackUp[2];
textureLoader attackDown[2];

player::player()
{
    //ctor
    verticies[0].x = 0.0;
    verticies[0].y = 0.0;
    verticies[0].z = -1.0;

    verticies[1].x = 1.0;
    verticies[1].y = 0.0;
    verticies[1].z = -1.0;

    verticies[2].x = 1.0;
    verticies[2].y = 1.0;
    verticies[2].z = -1.0;

    verticies[3].x = 0.0;
    verticies[3].y = 1.0;
    verticies[3].z = -1.0;

    runspeed = 0;
    jumpspeed = 0;
    actionTrigger = 0;

    xs = -4.5;
    ys = 0.5;
    zs = -7.0;

    standDir = 2;
}

player::~player()
{
    //dtor
}

void player::drawPlayer()
{
    //glColor3f(1.0,0.0,0.0);
//    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1.0);
    glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);

    glTexCoord2f(1.0,1.0);
    glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);

    glTexCoord2f(1.0,0.0);
    glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);

    glTexCoord2f(0.0,0.0);
    glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);
    glEnd();
 //   glPopMatrix();
}

void player::playerInit()
{
    T->start();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    standLeft[0].bindTexture("images/Alice/standLeft.png");
    standRight[0].bindTexture("images/Alice/standRight.png");
    standUp[0].bindTexture("images/Alice/standUp.png");
    standDown[0].bindTexture("images/Alice/standDown.png");

    attackLeft[0].bindTexture("images/Alice/attackLeft.png");
    attackRight[0].bindTexture("images/Alice/attackRight.png");
    attackUp[0].bindTexture("images/Alice/attackUp.png");
    attackDown[0].bindTexture("images/Alice/attackDown.png");


}

void player::actions(int action)
{
    switch(action)
    {
    case 0:
        glPushMatrix();
        glTranslated(xs,ys,zs);      // where the player is on the  map when they are standing

        if (standDir == 1)
        {
            standLeft[0].binder();
        }
        else if (standDir == 2)
        {
            standRight[0].binder();
        }
        else if (standDir == 3)
        {
            standUp[0].binder();
        }
        else if (standDir == 4)
        {
            standDown[0].binder();
        }
        drawPlayer();
        glPopMatrix();
        break;

    case 1:
        standDir = 1;
        glPushMatrix();
        glTranslated(xs,ys,zs);

        if (T->getTicks() > 15)
        {
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();
        }

      //  runText[runspeed].binder();
       // drawPlayer();

        glPopMatrix();
        break;

    case 2:
        standDir = 2;
        glPushMatrix();
        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > 15)
        {
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();
        }

  //      runText[runspeed].binder();
       // drawPlayer();

        glPopMatrix();
        break;

    case 3:
        standDir = 3;
        glPushMatrix();
        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > 15)
        {
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();
        }

 //       runText[runspeed].binder();
      //  drawPlayer();

        glPopMatrix();
        break;

    case 4:
        standDir = 4;
        glPushMatrix();
        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > 15)
        {
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();
        }

  //      runText[runspeed].binder();
      //  drawPlayer();
        glPopMatrix();
        break;
    case 5:
        glPushMatrix();
        glTranslated(xs,ys,zs);
            if (standDir == 1)
            {
                attackLeft[0].binder();
            }
            else if (standDir == 2)
            {
                attackRight[0].binder();
            }
            else if (standDir == 3)
            {
                attackUp[0].binder();
            }
            else if (standDir == 4)
            {
                attackDown[0].binder();
            }
            drawPlayer();
        glPopMatrix();
    break;
    }

}

void player::undoAttack()
{
    cout << "here" << endl;
    actions(1);
}

void player::addXS()
{
    xs += 0.02;
}

void player::subXS()
{
    xs -= 0.02;
}

void player::addYS()
{
    ys += 0.02;
}

void player::subYS()
{
    ys -= 0.02;
}



