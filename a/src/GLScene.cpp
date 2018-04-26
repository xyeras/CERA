#include <loadShader.h>

#include <GLScene.h>
#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <sounds.h>
#include <textureLoader.h>
#include <timer.h>
#include <Fonts.h>
#include <Particles.h>
#include <Objects.h>

Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
player *ply = new player();
skyBox *sky = new skyBox;
//sounds *snds = new sounds();
timer *T1 = new timer();
Particles *p = new Particles();

Fonts *F= new Fonts();
textureLoader *objtex = new textureLoader();
textureLoader *objtex2 = new textureLoader();

Objects obj[20];

loadShader *shader = new loadShader();
loadShader *shaderP = new loadShader();     // for particles

GLUquadricObj *quadric;
textureLoader earth;
textureLoader crate;
GLfloat position[] = {1.0,3.0,3.5,1.0};
GLdouble spin =0;

GLScene::GLScene()
{
    //ctor
    screenHeight= GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glewInit();

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL);
    GLLight SetLight(GL_LIGHT0);
    GLLight Light(GL_LIGHT0);

    modelTeapot->modelInit("images/player/player0.png",true);
    plx->parallaxInit("images/2.jpg");
    ply->playerInit();
    sky->loadTextures();
    T1->start();
//    snds->initSounds();

    F->initFonts("images/font.png");
    F->buildFont("AaA");
 //   snds->playMusic("sounds/MF-W-90.XM");

    quadric=gluNewQuadric();
    gluQuadricTexture(quadric,1);
    earth.bindTexture("images/3.jpg");
    crate.bindTexture("images/crate.png");
    shader->initShader("v.vs", "f.fs");
    shaderP->initShader("v1.vs", "f1.fs");
        glTexCoord2f(0.0,0.0);
        glVertex3f(1.0,1.0,1.0);
    objtex->bindTexture("images/flower.png");
    objtex2->bindTexture("images/flower2.png");
    for (int i = 0;i<20;i++)
    {
        if (i >= 0 && i < 6)
        {
            obj[i].objectTex = objtex->tex;
        }
        else
        {
            obj[i].objectTex = objtex2->tex;
        }



        obj[i].xPos = (float)(rand()%25)/10.0;
        obj[i].yPos = (float)(rand()%12)/10.0;

        obj[i].ySize = obj[i].xSize = (float)(rand()%12)/30.0;
    }
    return true;
}

float a=0;
int h=1;

GLint GLScene::drawGLScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix


    glPushMatrix();
      glScaled(3.33,3.33,1.0);
         plx->drawSquare(screenWidth,screenHeight);
     glPopMatrix();
       plx->scroll(false,"right",0.005);

       for (int i = 0;i < 20;i++)
       {
           obj[i].rotateZ>=360?obj[i].rotateZ=0.0: obj[i].rotateZ +=0.5;
           obj[i].drawObjects();
       }

        glUseProgram(shaderP->program);
       glPushMatrix();
    glTranslated(0.6,-1.25,0.0);

    p->generateParticles();
    p->drawParticles();
    p->lifeTime();
    glColor3f(1.0,1.0,1.0);
    glPopMatrix();
    glUseProgram(0);
/*
    glPushMatrix();
        glDisable(GL_LIGHTING);
        glScaled(200,200,200);
        sky->drawBox();
        glEnable(GL_LIGHTING);
    glPopMatrix();
*/
    glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslated(0,-1.2,-4);
        ply->actions(ply->actionTrigger);
    glPopMatrix();

    glPushMatrix();
    earth.binder();
    glEnable(GL_LIGHTING);

    glTranslated(-3,2,-9);
      glRotated(90,1,0,0);
      glRotated(90,0,0,1);
      gluSphere(quadric,2,40,40);
      glRotated(-spin,0.0,0.0,1.0);
      glLightfv(GL_LIGHT0, GL_POSITION, position);

      glDisable(GL_LIGHTING);
    glPopMatrix();


     if(T1->getTicks()>15){
        (spin>360)?spin =0:spin +=2.0;
        T1->reset();
       }


     glPushMatrix();

    glUseProgram(shader->program); // adds texture code


    GLint loc = glGetUniformLocation(shader->program, "Scale");
    if (loc != -1) {
    glUniform1f(loc, a); // assign scale to be 4
    }

 // draw something
   glTranslated(0,0.0,-6);
   crate.binder();
   glBegin(GL_TRIANGLES);

      glTexCoord2f(1,1);
      glVertex3f(-3.0,0.0,0.0);
      glTexCoord2f(1,0);
      glVertex3f(0.0,-2.0,0.0);
      glTexCoord2f(0,1);
      glVertex3f(0.0,0.0,0.0);
    glEnd();

    glUseProgram(0);
    glPopMatrix();


    for(int i=0; i<F->cCnt;i++)
    {
        glPushMatrix();
        glTranslated(F->xpos+i/14.0,F->ypos,F->zoom);
          F->drawFont(i);
        glPopMatrix();
    }




    (a<0.1)?h=1:NULL;
    (a>1.5)?h=-1:NULL;
    a+=0.01*h;
}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
   GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
   glViewport(0,0,width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0,aspectRatio,0.1,1000);

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
	        KbMs->keyEnv(plx, 0.005);
	        KbMs->keyPressed(ply);
	        KbMs->keyPressed(sky);
//	        KbMs->keySound(snds);

	    break;

	    case WM_KEYUP:								// Has A Key Been Released?
		{
			KbMs->wParam = wParam;
			KbMs->keyUP();
			KbMs->keyUp(ply);
		break;								// Jump Back
		}

		case WM_LBUTTONDOWN:
        {
            KbMs->wParam = wParam;
   //         KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

   		case WM_RBUTTONDOWN:
        {
            KbMs->wParam = wParam;
      //      KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

          case WM_MBUTTONDOWN:
        {
            KbMs->wParam = wParam;
 //           KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            KbMs->mouseEventUp();
        break;								// Jump Back
        }

        case WM_MOUSEMOVE:
        {
             KbMs->mouseMove(modelTeapot, LOWORD(lParam),HIWORD(lParam));
             KbMs->mouseMove(sky,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

        case WM_MOUSEWHEEL:
        {
            KbMs->mouseWheel(modelTeapot,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;								// Jump Back
        }
}
}
