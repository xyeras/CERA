#include "GLScene.h"
#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <parallax.h>
#include <player.h>
#include <sounds.h>
#include <iostream>
using namespace std;
Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
parallax *plx2 = new parallax();
parallax *plx3 = new parallax();
parallax *plx4 = new parallax();
parallax *plx5 = new parallax();
player *ply = new player();
sounds *snds = new sounds();

GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    ActiveScene = 6;
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL);
    GLLight Light(GL_LIGHT0);
  //  modelTeapot->modelInit("images/player/player0.png",true);

  switch(ActiveScene)
  {


  case 1:          // Start Screen background & sound

    plx2->parallaxInit("images/TitleScreen.png");
    snds->playMusic("sounds/nightmare.wav");
    break;

  case 2:          // first comic strip
   // plx3->parallaxInit("images/");
   snds->playMusic("sounds/comic1.wav");
   break;

  case 3:          // second comic strip
    // plx4->parallaxInit("images/");
    snds->playMusic("sounds/creepy-music-box.wav");
   break;

  case 4:          // Level 1 background & sounds

    plx->parallaxInit("images/df.png");
    ply->playerInit(-4.5,0.5,-7.0,2,ActiveScene); // load xpos, ypos, zpos , direction to stand, scene number
    //snds->playMusic("sounds/forest_revised.wav");
    snds->playMusic("sounds/forest.mp3");
    //snds->playMusic("sounds/wind.wav");
    break;

   case 5:          // Level 2 background & sounds

    plx5->parallaxInit("images/dungeon.png");
    snds->playMusic("sounds/dungeon.wav");
    ply->playerInit(-.42,-2.98,-7.0,3,ActiveScene);

    break;

   case 6:
    //plx5->parallaxInit("images/dungeon.png");
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
        glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx->drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        glPushMatrix();
            ply->actions(ply->actionTrigger);
        glPopMatrix();
        break;

    case 5:             // Level 2 background & player
        glPushMatrix();
            glScaled(3.33,3.33,1.0);        // scale of environment
            plx5->drawSquare(screenWidth,screenHeight);
        glPopMatrix();

        glPushMatrix();
            ply->actions(ply->actionTrigger);
        glPopMatrix();
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

            break;
            }


        }       // end of inner switch for inputs
        break;
        //--------------------------------------------------------------

    case 4:         // Level 1 Inputs

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
                KbMs->mouseEventDown(ply);
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
                KbMs->mouseEventDown(ply);
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
