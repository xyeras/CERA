#include <loadShader.h>
#include "GLScene.h"
#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <parallax.h>
#include <player.h>
#include <sounds.h>
#include <iostream>
#include <enms.h>
#include <string.h>
#include <enms2.h>
#include <rain.h>
#include <windows.h>
using namespace std;
timer *Te = new timer();
Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
parallax *plx2 = new parallax();
parallax *plx3 = new parallax();
parallax *plx4 = new parallax();
parallax *plx5 = new parallax();
parallax *plx6 = new parallax();
parallax *plx7 = new parallax();
parallax *plx8 = new parallax();
parallax *plx9 = new parallax();
loadShader *shader = new loadShader();
player *ply = new player();
sounds *snds = new sounds();
textureLoader *enm = new textureLoader();
textureLoader *enm2 = new textureLoader();
textureLoader *att = new textureLoader();
textureLoader *att2 = new textureLoader();
rain *R = new rain();
enms E;
enms arr2[3];
enms2 E2;
enms2 arr[3];
float a=0;
int h=1;
GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    ActiveScene =1;
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glewInit();
    int x,z;
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL);
    GLLight Light(GL_LIGHT0);
  //  modelTeapot->modelInit("images/player/player0.png",true);
    shader->shaderInit("V.vs","F.fs");
  switch(ActiveScene)
  {


  case 1:          // Start Screen background & sound

    plx2->parallaxInit("images/title.png");
    snds->playMusic("sounds/nightmare.wav");
    break;

  case 2:          // first comic strip
    plx3->parallaxInit("images/Story/scene1.jpg");
   snds->playMusic("sounds/comic1.wav");
   break;

  case 3:          // second comic strip
     plx4->parallaxInit("images/Story/scene2.jpg");
    snds->playMusic("sounds/creepy-music-box.wav");
   break;

  case 4:          // Level 1 background & sounds
//    E2.initAttack(2);
    plx->parallaxInit("images/df.png");
    ply->playerInit(-4.5,0.5,-7.0,2,ActiveScene); // load xpos, ypos, zpos , direction to stand, scene number
    //snds->playMusic("sounds/forest_revised.wav");
    snds->playMusic("sounds/forest.mp3");
    //snds->playMusic("sounds/wind.wav");
    att->bindTexture("images/Demon attacks/DA10.png");
    for(int i=0;i<1;i++)
    {
        arr[i].arrTex = att->tex;
        arr[i].arrowLoc.sizes=1;
    }

    enm2->bindTexture("images/demon test.png");
    E2.EnemyTex= enm2->tex;
    //E.xPos = (float)(rand()) / float(RAND_MAX)*5-2.5;
    //E.yPos = -0.5;
    E2.placeEnemy(1,0.3,-3.0);
    E2.ySize=E2.xSize= 0.3;
    shader->shaderInit("V1.vs","F1.fs");
    break;

   case 5:          // Level 2 background & sounds

    plx5->parallaxInit("images/dungeon.png");
    snds->playMusic("sounds/dungeon.wav");
    ply->playerInit(-.42,-2.98,-7.0,3,ActiveScene);
    att2->bindTexture("images/attack boss 2/MA1.png");
    for(int i=0;i<1;i++)
    {
        arr2[i].arrTex = att2->tex;
        arr2[i].arrowLoc.sizes=5;
    }
    enm->bindTexture("images/dragon attack.png");
    E.EnemyTex= enm->tex;
    //E.xPos = (float)(rand()) / float(RAND_MAX)*5-2.5;
    //E.yPos = -0.5;
    E.placeEnemy(1,0.5,-3.0);
    E.ySize=E.xSize= 0.3;

    break;

   case 6:
    plx5->parallaxInit("images/Story/scene3.jpg");
    snds->playMusic("sounds/calm-synthesizer.wav");
    break;

  }
    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

    switch(ActiveScene)
    {

    case 1:             // Start Screen
        glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx2->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;
    case 2:             // draw first comic strip
        glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx3->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;
    case 3:             // draw second comic strip
        glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx4->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case 4:             // Level 1 background & player

        {int i, j;
        float x, y, z;
        glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx->drawSquare(screenWidth,screenHeight);

        glPopMatrix();

        glUseProgram(shader->program);
        GLint loc=glGetUniformLocation(shader->program,"Scale");
        if(loc!=-1)
        {
            glUniform1f(loc,a);
        }
        glPushMatrix();
            glTranslated(0.6,-1.25,0.0);
            R->generateParticles();
            R->drawParticles();
            R->lifeTime();
            glColor3f(1,1,1);
        glPopMatrix();
        glUseProgram(0);
      (a<0.1)?h=1:NULL;
      (a>1.5)?h=-1:NULL;
      a+=0.01*h;

        glPushMatrix();
            ply->actions(ply->actionTrigger);
        glPopMatrix();



        glPushMatrix();
            if(E2.yPos<-0.65)
            {
                E2.action =0;
                E2.ymove = 0.0015;
            //E2.arrowLoc.x-=0.01;
            }

            else if(E2.yPos>0.75)
            {
                E2.action =1;
                E2.ymove = -0.0015;
                //E2.arrowLoc.x-=0.01;
            }
            E2.yPos += E2.ymove;
            E2.actions();
        glPopMatrix();

        glPushMatrix();
        float deltaX4;
        float deltaY4;
        float dist4;
        for(int i=0;i<1;i++)
        {

            arr[i].drawAttack();
            arr[i].arrowLoc.x-=0.005;

            // calculate collision of player with fireball
            deltaX4 = ply->getXS() - arr[i].arrowLoc.x;
            deltaY4 = ply->getYS() - arr[i].arrowLoc.y+0.3;
            dist4 = sqrtf((deltaX4 * deltaX4)+(deltaY4 * deltaY4));

            //cout << "lives " << ply->lives << endl;
            if (dist4 <= 1.53)              // Alice gets hit
            {
              //     cout << "hit--------------------------" << endl;
                ply->lives -= 1;

                // reset hit
                arr[i].arrowLoc.x=E2.xPos;
                arr[i].arrowLoc.y=E2.yPos;
                if (ply->lives == 0)
                {
                    //reset Alice's live before moving on to next scene
                    //ply->lives = 3;
                    ply->isAlive=false;
                    // Alice dies-------------------------------------------------------------------------------

                }
            }

            if(arr[i].arrowLoc.x<=-3.00)
            {
                arr[i].arrowLoc.x=E2.xPos;
                arr[i].arrowLoc.y=E2.yPos;
            }
        }

        glPopMatrix();



        if(paused){
                glPushMatrix();
                glScaled(3.33, 3.33, 1.0);
                    plx6->drawSquare(screenWidth,screenHeight);
                    glPopMatrix();
                cout<<"ISPAUSED"<<endl;
            }
        }
        break;

    case 5:             // Level 2 background & player
        glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx5->drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        glPushMatrix();
            ply->actions(ply->actionTrigger);
        glPopMatrix();




        glPushMatrix();
            if(E.xPos<-1.55)
            {
                E.action =0;
                E.xmove = 0.0025;
            }
            else if(E.xPos>1.55)
            {
                E.action =1;
                E.xmove = -0.0025;
            }
            if(E.isEnemyLive)
            {
                E.xPos += E.xmove;
                E.actions();
            }else if(!E.isEnemyLive)
            {
//                 if(!KbMs->mouseEventDown(ply,E))
//                 {
//                     E.actions();
                    //Sleep(3000);
                    cout<<"woahhhhh there"<<endl;
                    snds->stopAllSounds();

                    callLevelChanger(6);
                    plx5->parallaxInit("images/Story/scene3.jpg");
                    snds->playMusic("sounds/calm-synthesizer.wav");


            }
        glPopMatrix();
        glPushMatrix();
        float deltaX5;
        float deltaY5;
        float dist5;
        for(int i=0;i<1;i++)
        {

            arr2[i].drawAttack();
            arr2[i].arrowLoc.y-=0.03;

             // calculate collision of player with fireball
            deltaX5 = ply->getXS() - arr2[i].arrowLoc.x+0.5;
            deltaY5 = ply->getYS() - arr2[i].arrowLoc.y+3.0;
            dist5 = sqrtf((deltaX5 * deltaX5)+(deltaY5 * deltaY5));

           // cout << "d " << dist5 << endl;
            //cout << "lives " << ply->lives << endl;
            if (dist5 <= .05)              // Alice gets hit
            {
                  cout << "hit--------------------------" << endl;

                ply->lives -= 1;
                    cout<<ply->lives<<endl;
                // reset hit
                arr2[i].arrowLoc.x=E.xPos;
                arr2[i].arrowLoc.y=E.yPos;
                if (ply->lives == 0)
                {
                    //reset Alice's live before moving on to next scene
                    ply->isAlive=false;
                    // Alice dies-------------------------------------------------------------------------------
                }
            }


            if(arr2[i].arrowLoc.y<=-3.00)
            {
                arr2[i].arrowLoc.x=E.xPos;
                arr2[i].arrowLoc.y=E.yPos;
            }
        }

        glPopMatrix();

//        if(!E.isEnemyLive)
//        {
//            enm->bindTexture("images/demon attack.png");
//            E.EnemyTex= enm->tex;
//            //E.xPos = (float)(rand()) / float(RAND_MAX)*5-2.5;
//            //E.yPos = -0.5;
//
//            E.ySize=E.xSize= 0.3;
//        }
        break;

    case 6:
       glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx5->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;
        case 7:
      glPushMatrix();
           glScaled(3.33,3.33,1.0);        // scale of environment
           plx6->drawSquare(screenWidth,screenHeight);
       glPopMatrix();
        break;
    case 8:
  glPushMatrix();
       glScaled(3.33,3.33,1.0);        // scale of environment
       plx7->drawSquare(screenWidth,screenHeight);
   glPopMatrix();
    break;
    case 9:
  glPushMatrix();
       glScaled(3.33,3.33,1.0);        // scale of environment
       plx8->drawSquare(screenWidth,screenHeight);
   glPopMatrix();
    break;
    case 10:
  glPushMatrix();
       glScaled(3.33,3.33,1.0);        // scale of environment
       plx9->drawSquare(screenWidth,screenHeight);
   glPopMatrix();
    break;
    }


}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
   GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
   glViewport(0,0,width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0,aspectRatio,0.1,100);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(ActiveScene)
    {
    case 1:         // Start Screen Inputs
        switch (uMsg)									// Check For Windows Messages
        {

            case WM_KEYDOWN:
                KbMs->wParam = wParam;

                switch(wParam){
            case 0x53: //'s'
                snds->Plays("sounds/sword_sound.wav");
                snds->stopAllSounds();
                callLevelChanger(2);

                plx3->parallaxInit("images/Story/scene1.jpg");
                snds->playMusic("sounds/comic1.wav");
//
                cout<<"Game Start!"<<endl;
                //snds->stopAllSounds();
                break;

            case 0x48://h
                snds->Plays("sounds/sword_sound.wav");
                callLevelChanger(10);
                plx9->parallaxInit("images/howToPlay.png");
                break;

            case 0x43://credits
                snds->Plays("sounds/sword_sound.wav");
                //snds->stopAllSounds();
                callLevelChanger(10);
                plx9->parallaxInit("images/credits.png");
                //pausedScene = 4;
                returnScene = 1;
                break;
            case 0x45: //'E'
                snds->Plays("sounds/sword_sound.wav");
                exit(0);
                break;
                }

            break;

            break;


            case WM_LBUTTONDOWN:
            {
                KbMs->wParam = wParam;

            break;
            }


        }       // end of inner switch for inputs
        break;
        //--------------------------------------------------------------
    case 2:            // first comic strip inputs
        switch (uMsg)									// Check For Windows Messages
        {

            case WM_KEYDOWN:
                KbMs->wParam = wParam;

            break;


            case WM_LBUTTONDOWN:
            {
                KbMs->wParam = wParam;
                snds->stopAllSounds();
                callLevelChanger(3);
                plx4->parallaxInit("images/Story/scene2.jpg");
            snds->playMusic("sounds/creepy-music-box.wav");

            break;
            }


        }       // end of inner switch for inputs
        break;
        //--------------------------------------------------------------

    case 3:             // second comic strip inputs
        switch (uMsg)									// Check For Windows Messages
        {

            case WM_KEYDOWN:
                KbMs->wParam = wParam;

            break;


            case WM_LBUTTONDOWN:
            {
                KbMs->wParam = wParam;
                snds->stopAllSounds();
                callLevelChanger(4);
                plx->parallaxInit("images/df.png");
                ply->playerInit(-4.5,0.5,-7.0,2,ActiveScene); // load xpos, ypos, zpos , direction to stand, scene number
                snds->playMusic("sounds/forest.mp3");
                att->bindTexture("images/Demon attacks/DA10.png");
    for(int i=0;i<3;i++)
    {
        arr[i].arrTex = att->tex;
        arr[i].arrowLoc.sizes=1;
    }
                 enm2->bindTexture("images/demon test.png");
            E2.EnemyTex= enm2->tex;
            //E.xPos = (float)(rand()) / float(RAND_MAX)*5-2.5;
            //E.yPos = -0.5;
            E2.placeEnemy(1,0.5,-3.0);
            E2.ySize=E2.xSize= 0.3;
            shader->shaderInit("V1.vs","F1.fs");

            break;
            }


        }       // end of inner switch for inputs
        break;
        //--------------------------------------------------------------

    case 4:         // Level 1 Inputs
        if(!ply->isAlive)
        {
            ply->isAlive=true;
            ply->lives=3;
            snds->stopAllSounds();
                callLevelChanger(5);
                plx5->parallaxInit("images/dungeon.png");
        snds->playMusic("sounds/dungeon.wav");
        ply->playerInit(-.42,-2.98,-7.0,3,ActiveScene);
            att2->bindTexture("images/attack boss 2/MA1.png");
            for(int i=0;i<1;i++)
            {
                arr2[i].arrTex = att2->tex;
                arr2[i].arrowLoc.sizes=5;
            }
            enm->bindTexture("images/dragon attack.png");
            E.EnemyTex= enm->tex;
    //E.xPos = (float)(rand()) / float(RAND_MAX)*5-2.5;
    //E.yPos = -0.5;
        E.placeEnemy(1,0.5,-3.0);
        E.ySize=E.xSize= 0.3;
        }
        switch (uMsg)									// Check For Windows Messages
        {

            case WM_KEYDOWN:
                {
                KbMs->wParam = wParam;
                KbMs->keyPressed(modelTeapot);
             //   KbMs->keyEnv(plx,0.005);          // for environment to move around player
                KbMs->keyPressed(ply);
                KbMs->keySounds(snds,ply->inScene);
                switch(wParam){
            case VK_RETURN:
                snds->stopAllSounds();
                callLevelChanger(7);
                plx6->parallaxInit("images/pause.png");
                pausedScene = 4;
                returnScene = 2;
                }
                break;
                }
            break;

            case WM_KEYUP:								// Has A Key Been Released?
            {
                KbMs->wParam = wParam;
                //KbMs->keyUP();
                KbMs->keyUP(ply);
            break;								// Jump Back
            }

            case WM_LBUTTONDOWN:
            {
                KbMs->wParam = wParam;
                KbMs->mouseEventDown3(ply);
                KbMs->mouseEventDown(snds);
            break;								// Jump Back
            }



            case WM_LBUTTONUP:
            {
                KbMs->mouseEventUp(ply);
            break;								// Jump Back
            }

        }       // end of inner switch for inputs
        break;

    //--------------------------------------------------------------------

    case 5:         // Level 2 Inputs
//        if(!ply->isAlive)
//        {
//            cout<<"U DEAD"<<endl;
//            exit(0);
//        }

        switch (uMsg)									// Check For Windows Messages
        {

            case WM_KEYDOWN:
                KbMs->wParam = wParam;
                KbMs->keyPressed(modelTeapot);
             //   KbMs->keyEnv(plx,0.005);          // for environment to move around player
                KbMs->keyPressed(ply);
                KbMs->keySounds(snds,ply->inScene);
                switch(wParam){
            case VK_RETURN:
                snds->stopAllSounds();
                callLevelChanger(7);
                plx6->parallaxInit("images/pause.png");
                pausedScene = 5;
                returnScene = 3;
                }
                break;
            break;

            case WM_KEYUP:								// Has A Key Been Released?
            {
                KbMs->wParam = wParam;
                //KbMs->keyUP();
                KbMs->keyUP(ply);
            break;								// Jump Back
            }

            case WM_LBUTTONDOWN:
            {
                KbMs->wParam = wParam;

                KbMs->mouseEventDown(ply,E);
                KbMs->mouseEventDown(snds);
                //if(!KbMs->mouseEventDown(ply,E)&&!E.isEnemyLive)
//                if(!E.isEnemyLive)
//                {
                    if(!E.isEnemyLive)
                    {
                        enm->bindTexture("images/dragon die.png");
                        E.EnemyTex= enm->tex;
                        E.ySize=E.xSize= 0.3;


                     //Sleep(3000);
                    cout<<"now im here"<<endl;
                    snds->stopAllSounds();

                    callLevelChanger(6);
                    plx5->parallaxInit("images/Story/scene3.jpg");
                    snds->playMusic("sounds/calm-synthesizer.wav");}
//                }
            break;								// Jump Back
            }



            case WM_LBUTTONUP:
            {
                KbMs->mouseEventUp(ply);
            break;								// Jump Back
            }

        }       // end of inner switch for inputs
        break;

        case 6:            // third comic strip inputs
        switch (uMsg)									// Check For Windows Messages
        {

            case WM_KEYDOWN:
                KbMs->wParam = wParam;

            break;


            case WM_RBUTTONDOWN:
            {
                cout<<endl;
                cout<<"*************GAME WON?*************"<<endl;
                exit(0);
                KbMs->wParam = wParam;

            break;
            }


        }       // end of inner switch for inputs
        break;
        case 7:            // first comic strip inputs
        switch (uMsg)									// Check For Windows Messages
        {
            case WM_KEYDOWN:
                KbMs->wParam = wParam;

                switch(wParam){
                case 0x52: //Return
                    //snds->stopAllSounds();
                    callLevelChanger(pausedScene);
                    cout<<"RETURNEDDDDDDDDDDDD";
                    cout<<pausedScene<<endl;
                    if(pausedScene ==4) {plx6->parallaxInit("images/df.png");snds->playMusic("sounds/forest.mp3");}
                    else{snds->playMusic("sounds/dungeon.wav");}
                break;

                case 0x48: //How to play
                //snds->Plays("sounds/sword_sound.wav");
                //callLevelChanger(4);
                plx->parallaxInit("images/howToPlay.png");
                break;

                case 0x42: // Back to start menu
                    callLevelChanger(1);
                    plx2->parallaxInit("images/title.png");
                break;

                }

                break;


        }       // end of inner switch for inputs
            case 8:            // first comic strip inputs
        switch (uMsg)									// Check For Windows Messages
        {
            case WM_KEYDOWN:
                KbMs->wParam = wParam;

                switch(wParam){
                case 0x52:
                    if(returnScene == 1){
                    callLevelChanger(1);
                    plx2->parallaxInit("images/title.png");
                    }
                    if(returnScene ==2){
                        callLevelChanger(4);
                        plx->parallaxInit("images/df.png");
                    }
                    if(returnScene == 3){
                        callLevelChanger(5);
                        plx5->parallaxInit("images/dungeon.png");
                    }
                }

                break;


        }
        break;

    case 9:            // first comic strip inputs
        switch (uMsg)									// Check For Windows Messages
        {
            case WM_KEYDOWN:
                KbMs->wParam = wParam;

                switch(wParam){
                case 0x42:
                    callLevelChanger(1);
                    plx2->parallaxInit("images/title.png");
                }
                break;
        }
        break;
                case 10:

                    switch(wParam)
                    {
                        case 0x42:
                            callLevelChanger(1);
                             plx9->parallaxInit("images/title.png");
                            break;
                        case 0x52:
                            callLevelChanger(1);
                             plx9->parallaxInit("images/title.png");
                            break;
                    }
        //--------------------------------------------------------------
    }

    //--------------------------------------------------------------------

}

void GLScene::resetData()
{
    cout<<"Reset"<<endl;
    cout<<ActiveScene;
}

void GLScene::callLevelChanger(int val)
{
    ActiveScene = val;
    resetData();
}

