#include "Inputs.h"
#include <Trees.h>
#include <math.h>

Trees *tree = new Trees();
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
    float deltaX1 = ply->getXS() - tree->getX(0);
    float deltaY1 = ply->getYS() - tree->getY(0);
    float dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

    float deltaX2 = ply->getXS() - tree->getX(1);
    float deltaY2 = ply->getYS() - tree->getY(1);
    float dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

    float deltaX3 = ply->getXS() - tree->getX(2);
    float deltaY3 = ply->getYS() - tree->getY(2);
    float dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));
    switch(wParam)
    {
        case VK_LEFT:
            ply->actionTrigger = 1;
            if (ply->getXS() >= -4.70)      // keeps in bounces of map
            {
                if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)   // allows player to move as long not within radius of tree
                {
                     ply->subXS();
                }
                else
                {
                    cout << "here 1" << endl;
                    // player is running into tree
                    // allows player to move if that move will not let them collide with the tree
                    deltaX1 = (ply->getXS() - 0.02) - tree->getX(0);
                    dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                    deltaX2 = (ply->getXS() - 0.02) - tree->getX(1);
                    dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                    deltaX3 = (ply->getXS() - 0.02) - tree->getX(2);
                    dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                    if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                    {
                        ply->subXS();
                    }
                }
            }
            break;

        case VK_RIGHT:      // does have a right boundary yet, needs next level goer
            ply->actionTrigger = 2;
            if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
            {
                ply->addXS();
            }
            else
            {
                cout << "here 2" << endl;
                deltaX1 = (ply->getXS() + 0.02) - tree->getX(0);
                dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                deltaX2 = (ply->getXS() + 0.02) - tree->getX(1);
                dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                deltaX3 = (ply->getXS() + 0.02) - tree->getX(2);
                dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                {
                    ply->addXS();
                }
            }
            break;

        case VK_UP:
            ply->actionTrigger = 3;
            if (ply->getYS() <= 1.92)
            {
                if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                {
                    ply->addYS();
                }
                else
                {
                    cout << "here 3" << endl;
                    deltaY1 = (ply->getYS() + 0.02) - tree->getY(0);
                    dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                    deltaY2 = (ply->getYS() + 0.02) - tree->getY(1);
                    dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                    deltaY3 = (ply->getYS() + 0.02) - tree->getY(2);
                    dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                    if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                    {
                        ply->addYS();
                    }
                }
            }
            break;

        case VK_DOWN:
            ply->actionTrigger = 4;
            if (ply->getYS() >= -2.36)
            {
                if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                {
                    ply->subYS();
                }
                else
                {
                    cout << "here 4" << endl;
                    deltaY1 = (ply->getYS() - 0.02) - tree->getY(0);
                    dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                    deltaY2 = (ply->getYS() - 0.02) - tree->getY(1);
                    dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                    deltaY3 = (ply->getYS() - 0.02) - tree->getY(2);
                    dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                    if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                    {
                        ply->subYS();
                    }
                }
            }
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
            //snds->Plays("sounds/walk.wav");
            break;

    }
}

void Inputs::mouseEventDown(sounds* snds)
{
    switch(wParam)
    {
        case MK_LBUTTON:
            snds->Plays("sounds/slash.wav");
            break;


    }
}

