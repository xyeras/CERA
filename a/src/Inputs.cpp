#include "Inputs.h"
#include <player.h>

vec3 Inputs::mouseGL(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    vec3 pos;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
  cout<<winZ<<endl;
  //winZ=100;
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &pos.x, &pos.y, &pos.z);
    return pos;
}



Inputs::Inputs()
{
    //ctor
   prev_Mouse_X =0;
   prev_Mouse_Y =0;
   Mouse_Translate=0;
   Mouse_Roatate=0;
}

Inputs::~Inputs()
{
    //dtor
}
void Inputs::keyEnv(parallax* plx, float speed)
{
    switch(wParam)
    {
        case VK_LEFT:
            plx->Xmin -=speed;
            plx->Xmax -=speed;
            break;

        case VK_RIGHT:
            plx->Xmin +=speed;
            plx->Xmax +=speed;
            break;

         case VK_UP:
            plx->Ymin -=speed;
            plx->Ymax -=speed;
            break;

        case VK_DOWN:
            plx->Ymin +=speed;
            plx->Ymax +=speed;
            break;
    }
}


void Inputs::keyPressed(Model* Mdl)
{
    switch(wParam)
    {
    case VK_LEFT:
        Mdl->RotateX +=1.0;
        break;

    case VK_RIGHT:
        Mdl->RotateX -=1.0;
        break;

    case VK_DOWN:
        Mdl->RotateY -=1.0;
        break;

    case VK_UP:
        Mdl->RotateY +=1.0;
        break;

    case VK_ADD:
        Mdl->Zoom +=1.0;
        break;

    case VK_SUBTRACT:
        Mdl->Zoom -=1.0;
        break;
    }
}

void Inputs::keyUp(player* ply)
{
    ply->actionTrigger =1;

    switch(wParam)
    {
       default:break;
    }
}


void Inputs::keyPressed(player* ply)
{
    switch(wParam)
    {
     case VK_LEFT:
       ply->actionTrigger =0;
        break;

    case VK_RIGHT:
       ply->actionTrigger =1;
        break;

    case VK_DOWN:

        break;

    case VK_UP:

        break;

    case VK_ADD:

        break;

    case VK_SUBTRACT:

        break;
    }
}


void Inputs::keyUP()
{
  switch (wParam)
            {
                default:
                break;
            }
}

void Inputs::mouseEventDown(player *ply, double x,double y)
{
        vec3 pos;
        prev_Mouse_X =x;
        prev_Mouse_Y =y;

   switch (wParam)
            {
                case MK_LBUTTON:
                        Mouse_Roatate = true;

                        pos = mouseGL((int)x,(int)y);
                        ply->Xpos = pos.x;
                        ply->Ypos = pos.y;
                        ply->Zpos = pos.z;

 cout<<x<<"  "<<ply->Xpos<<"  "<<y<<"  "<<ply->Ypos<<"  "<<ply->Zpos<<endl;

                    break;

                case MK_RBUTTON:
                     Mouse_Translate =true;
                    break;
                case MK_MBUTTON:

                    break;

                default:
                    break;
            }
}

 void Inputs::mouseEventUp()
 {
    Mouse_Translate =false;
    Mouse_Roatate =false;
 }

void Inputs::mouseWheel(Model *Model,double Delta)
{
    Model->Zoom += Delta/100;
}

void Inputs::mouseMove(Model *Model,double x,double y)
{
      if(Mouse_Translate)
      {
       Model->Xpos += (x-prev_Mouse_X)/100;
       Model->Ypos -= (y-prev_Mouse_Y)/100;

       prev_Mouse_X =x;
       prev_Mouse_Y =y;
      }

      if(Mouse_Roatate)
      {
        Model->RotateY += (x-prev_Mouse_X)/3;
        Model->RotateX += (y-prev_Mouse_Y)/3;

        prev_Mouse_X =x;
        prev_Mouse_Y =y;
      }
}
void Inputs::keyPressed(skyBox* sky)
{
    switch(wParam)
    {
     case VK_LEFT:
       sky->RotateY += 0.5;
        break;

    case VK_RIGHT:
       sky->RotateY -= 0.5;
        break;

    case VK_DOWN:
         sky->RotateX += 0.5;
        break;

    case VK_UP:
         sky->RotateX -= 0.5;
        break;
    }
}

void Inputs::mouseMove(skyBox* sky, double x, double y)
{

        sky->RotateY += (x-prev_Mouse_X)/3;
        sky->RotateX += (y-prev_Mouse_Y)/3;

        prev_Mouse_X =x;
        prev_Mouse_Y =y;

}
void Inputs::keySound(sounds* snds)
{
     switch(wParam)
    {
      case VK_SPACE:
//          snds->playSound("sounds/explosion.wav");
      break;
      case VK_TAB:
   //       snds->playMusic("sounds/MF-W-90.XM");
      break;
    }

}

