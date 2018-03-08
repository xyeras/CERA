#include <player.h>
#include <timer.h>
#include <textureLoader.h>

timer *T = new timer();
textureLoader runText[10];
textureLoader stand[2];

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

    stand[0].bindTexture("images/player/play.png");

    runText[0].bindTexture("images/player/player0.png");
    runText[1].bindTexture("images/player/player1.png");
    runText[2].bindTexture("images/player/player2.png");
    runText[3].bindTexture("images/player/player3.png");
    runText[4].bindTexture("images/player/player4.png");
    runText[5].bindTexture("images/player/player5.png");
    runText[6].bindTexture("images/player/player6.png");
    runText[7].bindTexture("images/player/player7.png");
    runText[8].bindTexture("images/player/player8.png");
    runText[9].bindTexture("images/player/player9.png");

}

void player::actions(int action)
{
    switch(action)
    {
    case 0:
        glPushMatrix();
        glTranslated(xs,ys,zs);      // where the player is on the  map when they are standing
        stand[0].binder();
        drawPlayer();
        glPopMatrix();
        break;

    case 1:
        glPushMatrix();
        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > 15)
        {
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();
        }

        runText[runspeed].binder();
        drawPlayer();

        glPopMatrix();
        break;

    case 2:
        glPushMatrix();
        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > 15)
        {
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();
        }

        runText[runspeed].binder();
        drawPlayer();

        glPopMatrix();
        break;

    case 3:
        glPushMatrix();
        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > 15)
        {
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();
        }

        runText[runspeed].binder();
        drawPlayer();

        glPopMatrix();
        break;

    case 4:
        glPushMatrix();
        glTranslated(xs,ys,zs);     // where the player is on the map when they are running

        if (T->getTicks() > 15)
        {
            runspeed++;
            runspeed = runspeed % 10;
            T->reset();
        }

        runText[runspeed].binder();
        drawPlayer();

        glPopMatrix();
        break;
    }

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



