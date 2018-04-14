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

        case VK_LEFT:
            ply->actionTrigger = 1;
            ply->subXS();
            break;

        case VK_RIGHT:
            ply->actionTrigger = 2;
            ply->addXS();
            break;

        case VK_UP:
            ply->actionTrigger = 3;
            ply->addYS();
            break;

        case VK_DOWN:
            ply->actionTrigger = 4;
            ply->subYS();
            break;

    }
}


void Inputs::mouseEventDown(player* ply)
{
    switch(wParam)
    {
        case MK_LBUTTON:
            ply->actionTrigger = 5;
            break;


    }
}


 void Inputs::mouseEventUp(player* ply)
 {
    //Mouse_Translate =false;
    //Mouse_Roatate =false;

            ply->actionTrigger = 0;
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

void Inputs::keySounds(sounds* snds)
{
    switch(wParam)
    {
        case VK_LEFT:
        case VK_RIGHT:
        case VK_UP:
        case VK_DOWN:
            snds->Plays("sounds/forest_walk.mp3");
            break;

    }
}

void Inputs::mouseEventDown(sounds* snds)
{
    switch(wParam)
    {
        case MK_LBUTTON:
            snds->Plays("sounds/sword_sound.wav");
            break;


    }
}

