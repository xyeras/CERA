#include "GLScene.h"
#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <parallax.h>
#include <player.h>
#include <sounds.h>

Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
player *ply = new player();
sounds *snds = new sounds();

GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
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
    plx->parallaxInit("images/df.png");
    ply->playerInit();
    snds->playMusic("sounds/forest_revised.wav");
    snds->playMusic("sounds/wind.wav");
    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix



    glPushMatrix();
        glScaled(3.33,3.33,1.0);        // scale of environment
        plx->drawSquare(screenWidth,screenHeight);
    glPopMatrix();
 //   plx->scroll(false,"left",0.005);
       glPushMatrix();
        ply->actions(ply->actionTrigger);
      //  modelTeapot->drawModel();
    glPopMatrix();
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
    switch (uMsg)									// Check For Windows Messages
	{

	    case WM_KEYDOWN:
	        KbMs->wParam = wParam;
	        KbMs->keyPressed(modelTeapot);
	     //   KbMs->keyEnv(plx,0.005);          // for environment to move around player
	        KbMs->keyPressed(ply);
	        KbMs->keySounds(snds);
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

    }
}
