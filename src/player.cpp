#include <player.h>
#include <timer.h>
#include <textureLoader.h>
#include <iostream>
#include <Trees.h>
#include <Posts.h>
#include <math.h>
using namespace std;
timer *T = new timer();
Trees *tree = new Trees();
Posts *light = new Posts();
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

switch(inScene)
    {

        case 4:
            {

                float deltaX1 = getXS() - tree->getX(0);
                float deltaY1 = getYS() - tree->getY(0);
                float dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                float deltaX2 = getXS() - tree->getX(1);
                float deltaY2 = getYS() - tree->getY(1);
                float dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                float deltaX3 = getXS() - tree->getX(2);
                float deltaY3 = getYS() - tree->getY(2);
                float dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

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

                     if (getXS() >= -4.70)      // keeps in bounces of map
                                {
                                    if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)   // allows player to move as long not within radius of tree
                                    {
                                         subXS();
                                    }
                                    else
                                    {
                                        // player is running into tree
                                        // allows player to move if that move will not let them collide with the tree
                                        deltaX1 = (getXS() - 0.06)- tree->getX(0);
                                        dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                                        deltaX2 = (getXS() - 0.06) - tree->getX(1);
                                        dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                                        deltaX3 = (getXS() - 0.06) - tree->getX(2);
                                        dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                                        if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                                        {
                                            subXS();
                                        }
                                    }
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

                    if (getXS() <= 3.76)
                    {
                        if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                        {
                            addXS();
                        }
                        else
                        {
                            deltaX1 = (getXS() + 0.06) - tree->getX(0);
                            dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                            deltaX2 = (getXS() + 0.06) - tree->getX(1);
                            dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                            deltaX3 = (getXS() + 0.06) - tree->getX(2);
                            dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                            if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                            {
                                addXS();
                            }
                        }
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

                    if (getYS() <= 1.92)
                    {
                        if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                        {
                            addYS();
                        }
                        else
                        {
                            deltaY1 = (getYS() + 0.06) - tree->getY(0);
                            dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                            deltaY2 = (getYS() + 0.06) - tree->getY(1);
                            dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                            deltaY3 = (getYS() + 0.06) - tree->getY(2);
                            dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                            if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                            {
                                addYS();
                            }
                        }
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

                    if (getYS() >= -2.36)
                    {
                        if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                        {
                            subYS();
                        }
                        else
                        {
                            deltaY1 = (getYS() - 0.06) - tree->getY(0);
                            dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                            deltaY2 = (getYS() - 0.06) - tree->getY(1);
                            dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                            deltaY3 = (getYS() - 0.06) - tree->getY(2);
                            dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                            if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                            {
                                subYS();
                            }
                        }
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


            break;
            }

        case 5:
            {
                float deltaX1L = getXS() - light->getX(0);
                float deltaY1L = getYS() - light->getY(0);
                float dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                float deltaX2L = getXS() - light->getX(1);
                float deltaY2L = getYS() - light->getY(1);
                float dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));

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

                    if (T->getTicks() > 60)
                    {
                        runspeed++;
                        runspeed = runspeed % 3;
                        T->reset();
                    }

                    if (getXS() >= -5.44)      // keeps in bounces of map
                    {
                        if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)   // allows player to move as long not within radius of post
                        {
                             subXS();
                        }
                        else
                        {
                            // player is running into post
                            // allows player to move if that move will not let them collide with the post
                            deltaX1L = (getXS() - 0.06)- light->getX(0);
                            dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                            deltaX2L = (getXS() - 0.06)- light->getX(1);
                            dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));


                            if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                            {
                                subXS();
                            }
                        }
                    }

                    standLeft[runspeed].binder();
                    drawPlayer();

                    glPopMatrix();
                    break;

                case 2:
                    glPushMatrix();


                    glTranslated(xs,ys,zs);     // where the player is on the map when they are running

                    if (T->getTicks() > 60)
                    {
                        runspeed++;
                        runspeed = runspeed % 3;
                        T->reset();
                    }

                    if (getXS() <= 4.33)
                    {
                        if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                        {
                            addXS();
                        }
                        else
                        {
                            deltaX1L = (getXS() + 0.06)- light->getX(0);
                            dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                            deltaX2L = (getXS() + 0.06)- light->getX(1);
                            dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));
                            if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                            {
                                addXS();
                            }
                        }
                    }

                    standRight[runspeed].binder();
                    drawPlayer();

                    glPopMatrix();
                    break;

                case 3:
                    glPushMatrix();

                    glTranslated(xs,ys,zs);     // where the player is on the map when they are running

                    if (T->getTicks() > 60)
                    {
                        runspeed++;
                        runspeed = runspeed % 3;
                        T->reset();
                    }

                    if (getYS() <= 1.92)
                    {
                        if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                        {
                            addYS();
                        }
                        else
                        {
                            deltaY1L = (getYS() + 0.06)- light->getY(0);
                            dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                            deltaY2L = (getYS() + 0.06)- light->getY(1);
                            dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));

                            if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                            {
                                addYS();
                            }
                        }
                    }

                    standUp[runspeed].binder();
                    drawPlayer();

                    glPopMatrix();
                    break;

                case 4:
                    glPushMatrix();

                    glTranslated(xs,ys,zs);     // where the player is on the map when they are running

                    if (T->getTicks() > 60)
                    {
                        runspeed++;
                        runspeed = runspeed % 3;
                        T->reset();
                    }

                    if (getYS() >= -3.0)
                    {
                        if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                        {
                            subYS();
                        }
                        else
                        {
                            deltaY1L = (getYS() - 0.06)- light->getY(0);
                            dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                            deltaY2L = (getYS() - 0.06)- light->getY(1);
                            dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));

                            if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                            {
                                subYS();
                            }
                        }
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
                            if (T->getTicks() > 60)
                            {
                                runspeed++;
                                runspeed = runspeed % 3;
                                T->reset();
                            }

                            attackLeft[runspeed].binder();
                        }
                        else if (standDir == 2)
                        {
                            if (T->getTicks() > 60)
                            {
                                runspeed++;
                                runspeed = runspeed % 3;
                                T->reset();
                            }

                            attackRight[runspeed].binder();
                        }
                        else if (standDir == 3)
                        {
                            if (T->getTicks() > 60)
                            {
                                runspeed++;
                                runspeed = runspeed % 3;
                                T->reset();
                            }

                            attackUp[runspeed].binder();
                        }
                        else if (standDir == 4)
                        {
                            if (T->getTicks() > 60)
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

            break;
            }
    }
}

void player::undoAttack()
{
    actions(1);
}

void player::addXS()
{
    switch(inScene)
    {
        case 4:
            xs += 0.004;
        break;

        case 5:
            xs +=0.006;
    }
}

void player::subXS()
{
    switch(inScene)
    {
        case 4:
            xs -= 0.004;
        break;

        case 5:
            xs -=0.006;
    }
}

void player::addYS()
{
    switch(inScene)
    {
        case 4:
            ys += 0.004;
        break;

        case 5:
            ys +=0.006;
    }
}

void player::subYS()
{
    switch(inScene)
    {
        case 4:
            ys -= 0.004;
        break;

        case 5:
            ys -=0.006;
    }
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





