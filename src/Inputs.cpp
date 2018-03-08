#include "Inputs.h"

Inputs::Inputs()
{
    //ctor
    prev_Mouse_X = 0;
    prev_Mouse_Y = 0;
    Mouse_Translate = 0;
    Mouse_Roatate = 0;
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
    {/*
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
*/
    case VK_ADD:
        Mdl->Zoom +=1.0;
        break;
    case VK_SUBTRACT:
        Mdl->Zoom -=1.0;
        break;
    }
}

void Inputs::keyUP(player* ply)
{
    ply->actionTrigger = 0;

    switch(wParam)
    {
        default:break;
    }
}

void Inputs::keyPressed(player* ply)
{
    switch(wParam)
    {
        case VK_ADD:
            ply->actionTrigger = 0;
            break;

        case VK_RIGHT:
            ply->actionTrigger = 1;
            ply->addXS();
            break;

        case VK_LEFT:
            ply->actionTrigger = 2;
            ply->subXS();
            break;

        case VK_UP:
            ply->actionTrigger = 3;
            ply->addYS();
            break;

        case VK_DOWN:
            ply->actionTrigger = 4;
            ply->subYS();
    }
}


void Inputs::mouseEventDown(Model *Model, double x,double y)
{
        prev_Mouse_X =x;
        prev_Mouse_Y =y;

   switch (wParam)
            {
                case MK_LBUTTON:
                        Mouse_Roatate = true;
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
