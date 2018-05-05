#include <player.h>
#include <timer.h>
#include <textureLoader.h>
#include <iostream>
using namespace std;
timer *T = new timer();
textureLoader runLeft[2];

// for moving player
textureLoader standLeft[2];
textureLoader standRight[2];
textureLoader standUp[2];
textureLoader standDown[2];

// for player's attack
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

void player::playerInit(float x, float y, float z, float sd, int sceneNum) // load xpos, ypos, zpos , direction to stand, scene number
{
    T->start();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    standLeft[0].bindTexture("images/improvedAlice/left1.png");
    standLeft[1].bindTexture("images/improvedAlice/left2.png");
    standLeft[2].bindTexture("images/improvedAlice/left3.png");

    standRight[0].bindTexture("images/improvedAlice/right1.png");
    standRight[1].bindTexture("images/improvedAlice/right2.png");
    standRight[2].bindTexture("images/improvedAlice/right3.png");

    standUp[0].bindTexture("images/improvedAlice/back1.png");
    standUp[1].bindTexture("images/improvedAlice/back2.png");
    standUp[2].bindTexture("images/improvedAlice/back3.png");

    standDown[0].bindTexture("images/improvedAlice/front1.png");
    standDown[1].bindTexture("images/improvedAlice/front2.png");
    standDown[2].bindTexture("images/improvedAlice/front3.png");

    attackLeft[0].bindTexture("images/improvedAlice/left1_attack.png");
    attackLeft[1].bindTexture("images/improvedAlice/left2_attack.png");
    attackLeft[2].bindTexture("images/improvedAlice/left3_attack.png");

    attackRight[0].bindTexture("images/improvedAlice/right1_attack.png");
    attackRight[1].bindTexture("images/improvedAlice/right2_attack.png");
    attackRight[2].bindTexture("images/improvedAlice/right3_attack.png");

    attackUp[0].bindTexture("images/improvedAlice/back1_attack.png");
    attackUp[1].bindTexture("images/improvedAlice/back2_attack.png");
    attackUp[2].bindTexture("images/improvedAlice/back3_attack.png");

    attackDown[0].bindTexture("images/improvedAlice/front1_attack.png");
    attackDown[1].bindTexture("images/improvedAlice/front2_attack.png");
    attackDown[2].bindTexture("images/improvedAlice/front3_attack.png");

    xs = x;
    ys = y;
    zs = z;

    standDir = sd;
    inScene = sceneNum;

}

void player::actions(int action)
{

    switch(action)
    {
    case 0: // not call case 0 (actionTrigger 0)
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
        glPushMatrix();


        glTranslated(xs,ys,zs);

        if (T->getTicks() > .05)
        {
            runspeed++;
            runspeed = runspeed % 3;
            T->reset();
        }

        standLeft[runspeed].binder();
        drawPlayer();

        glPopMatrix();
        break;

    case 2:
        glPushMatrix();


        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > .05)
        {
            runspeed++;
            runspeed = runspeed % 3;
            T->reset();
        }

        standRight[runspeed].binder();
        drawPlayer();

        glPopMatrix();
        break;

    case 3:
        glPushMatrix();

        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > .05)
        {
            runspeed++;
            runspeed = runspeed % 3;
            T->reset();
        }

        standUp[runspeed].binder();
        drawPlayer();

        glPopMatrix();
        break;

    case 4:
        glPushMatrix();

        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > .05)
        {
            runspeed++;
            runspeed = runspeed % 3;
            T->reset();
        }

        standDown[runspeed].binder();
        drawPlayer();
        glPopMatrix();
        break;
    case 5:
        glPushMatrix();
        glTranslated(xs,ys,zs);
            if (standDir == 1)
            {
                if (T->getTicks() > .05)
                {
                    runspeed++;
                    runspeed = runspeed % 3;
                    T->reset();
                }

                attackLeft[runspeed].binder();
            }
            else if (standDir == 2)
            {
                if (T->getTicks() > .05)
                {
                    runspeed++;
                    runspeed = runspeed % 3;
                    T->reset();
                }

                attackRight[runspeed].binder();
            }
            else if (standDir == 3)
            {
                if (T->getTicks() > .05)
                {
                    runspeed++;
                    runspeed = runspeed % 3;
                    T->reset();
                }

                attackUp[runspeed].binder();
            }
            else if (standDir == 4)
            {
                if (T->getTicks() > .05)
                {
                    runspeed++;
                    runspeed = runspeed % 3;
                    T->reset();
                }

                attackDown[runspeed].binder();
            }
            drawPlayer();
        glPopMatrix();
    break;
    }

}

void player::undoAttack()
{
    actions(1);
}

void player::addXS()
{
    xs += 0.06;
    cout << xs << endl;
}

void player::subXS()
{
    xs -= 0.06;
    cout << xs << endl;
}

void player::addYS()
{
    ys += 0.06;
    cout << ys << endl;
}

void player::subYS()
{
    ys -= 0.06;
    cout << ys << endl;
}

float player::getXS()
{
    return xs;
}

float player::getYS()
{
    return ys;
}

void player::setStandDir(int s)
{
    standDir = s;
}





