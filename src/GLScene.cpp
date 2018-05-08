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

using namespace std;
Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
parallax *plx2 = new parallax();
parallax *plx3 = new parallax();
parallax *plx4 = new parallax();
parallax *plx5 = new parallax();
parallax *plx6 = new parallax();
loadShader *shader = new loadShader();
player *ply = new player();
sounds *snds = new sounds();
textureLoader *enm = new textureLoader();
textureLoader *enm2 = new textureLoader();
rain *R = new rain();
enms E;
enms2 E2;
float a=0;
int h=1;
GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    ActiveScene = 5;
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

    plx->parallaxInit("images/df.png");
    ply->playerInit(-4.5,0.5,-7.0,2,ActiveScene); // load xpos, ypos, zpos , direction to stand, scene number
    //snds->playMusic("sounds/forest_revised.wav");
    snds->playMusic("sounds/forest.mp3");
    //snds->playMusic("sounds/wind.wav");
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
            }

            else if(E2.yPos>0.75)
            {
                E2.action =1;
                E2.ymove = -0.0015;
            }
            E2.yPos += E2.ymove;
            E2.actions();
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
            E.xPos += E.xmove;
            E.actions();
        glPopMatrix();

       // if(!E.isEnemyLive)
        //{

        //}
        break;

    case 6:
       glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx5->drawSquare(screenWidth,screenHeight);
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

            case 0x48:
                snds->Plays("sounds/sword_sound.wav");
                //callLevelChanger(4);
                plx->parallaxInit("images/howToPlay.png");
                break;


            case 0x45: //'E'
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
                paused = !paused;
                if(paused){
                    glEnable(GL_TEXTURE_2D);
                }
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
                //KbMs->mouseEventDown(ply,E);
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

        switch (uMsg)									// Check For Windows Messages
        {

            case WM_KEYDOWN:
                KbMs->wParam = wParam;
                KbMs->keyPressed(modelTeapot);
             //   KbMs->keyEnv(plx,0.005);          // for environment to move around player
                KbMs->keyPressed(ply);
                KbMs->keySounds(snds,ply->inScene);
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


            case WM_LBUTTONDOWN:
            {
                KbMs->wParam = wParam;

            break;
            }


        }       // end of inner switch for inputs
        break;
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

