#include "Inputs.h"
#include <Trees.h>
#include <Posts.h>
#include <math.h>
#include <iostream>
//#include <sounds.h>
using namespace std;
Trees *tree = new Trees();
Posts *light = new Posts();
//sounds *snds = new sounds();
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

    switch(ply->inScene)
    {
        case 1:
        {

        }

        case 4:
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
                    //ply->setStandDir(1);
                    ply->standDir = 1;              // sets the direction to stand after action

                    if (ply->getXS() >= -4.70)      // keeps in bounces of map
                    {
                        if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)   // allows player to move as long not within radius of tree
                        {
                             ply->subXS();
                        }
                        else
                        {
                            // player is running into tree
                            // allows player to move if that move will not let them collide with the tree
                            deltaX1 = (ply->getXS() - 0.06)- tree->getX(0);
                            dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                            deltaX2 = (ply->getXS() - 0.06) - tree->getX(1);
                            dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                            deltaX3 = (ply->getXS() - 0.06) - tree->getX(2);
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
                 //   ply->setStandDir(2);
                    ply->standDir = 2;

                    if (ply->getXS() <= 3.76)
                    {
                        if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                        {
                            ply->addXS();
                        }
                        else
                        {
                            deltaX1 = (ply->getXS() + 0.06) - tree->getX(0);
                            dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                            deltaX2 = (ply->getXS() + 0.06) - tree->getX(1);
                            dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                            deltaX3 = (ply->getXS() + 0.06) - tree->getX(2);
                            dist3 = sqrtf((deltaX3 * deltaX3)+(deltaY3 * deltaY3));

                            if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                            {
                                ply->addXS();
                            }
                        }
                    }
                    break;

                case VK_UP:
                    ply->actionTrigger = 3;
              //      ply->setStandDir(3);
                    ply->standDir = 3;
                    if (ply->getYS() <= 1.92)
                    {
                        if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                        {
                            ply->addYS();
                        }
                        else
                        {
                            deltaY1 = (ply->getYS() + 0.06) - tree->getY(0);
                            dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                            deltaY2 = (ply->getYS() + 0.06) - tree->getY(1);
                            dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                            deltaY3 = (ply->getYS() + 0.06) - tree->getY(2);
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
               //     ply->setStandDir(4);
                    ply->standDir = 4;
                    if (ply->getYS() >= -2.36)
                    {
                        if (dist1 >= 0.25 + 0.25 && dist2 >= 0.25 + 0.25 && dist3 >= 0.25 + 0.25)
                        {
                            ply->subYS();
                        }
                        else
                        {
                            deltaY1 = (ply->getYS() - 0.06) - tree->getY(0);
                            dist1 = sqrtf((deltaX1 * deltaX1)+(deltaY1 * deltaY1));

                            deltaY2 = (ply->getYS() - 0.06) - tree->getY(1);
                            dist2 = sqrtf((deltaX2 * deltaX2)+(deltaY2 * deltaY2));

                            deltaY3 = (ply->getYS() - 0.06) - tree->getY(2);
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
                break; // end of Level 1 inputs ----------------------------------------------------------

            case 5:
                {

                float deltaX1L = ply->getXS() - light->getX(0);
                float deltaY1L = ply->getYS() - light->getY(0);
                float dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                float deltaX2L = ply->getXS() - light->getX(1);
                float deltaY2L = ply->getYS() - light->getY(1);
                float dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));
                    switch(wParam)
                    {
                case VK_LEFT:
                    ply->actionTrigger = 1;
                    //ply->setStandDir(1);
                    ply->standDir = 1;              // sets the direction to stand after action

                    if (ply->getXS() >= -5.44)      // keeps in bounces of map
                    {
                        if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)   // allows player to move as long not within radius of post
                        {
                             ply->subXS();
                        }
                        else
                        {
                            // player is running into post
                            // allows player to move if that move will not let them collide with the post
                            deltaX1L = (ply->getXS() - 0.06)- light->getX(0);
                            dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                            deltaX2L = (ply->getXS() - 0.06)- light->getX(1);
                            dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));


                            if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                            {
                                ply->subXS();
                            }
                        }
                    }
                    break;

                case VK_RIGHT:
                    ply->actionTrigger = 2;
                    ply->standDir = 2;
                    if (ply->getXS() <= 4.33)
                    {
                        if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                        {
                            ply->addXS();
                        }
                        else
                        {
                            deltaX1L = (ply->getXS() + 0.06)- light->getX(0);
                            dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                            deltaX2L = (ply->getXS() + 0.06)- light->getX(1);
                            dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));
                            if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                            {
                                ply->addXS();
                            }
                        }
                    }


                    break;

                case VK_UP:
                    ply->actionTrigger = 3;
                    ply->standDir = 3;
                    if (ply->getYS() <= 1.92)
                    {
                        if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                        {
                            ply->addYS();
                        }
                        else
                        {
                            deltaY1L = (ply->getYS() + 0.06)- light->getY(0);
                            dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                            deltaY2L = (ply->getYS() + 0.06)- light->getY(1);
                            dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));

                            if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                            {
                                ply->addYS();
                            }
                        }
                    }
                    break;

                case VK_DOWN:
                    ply->actionTrigger = 4;
                    ply->standDir = 4;

                    if (ply->getYS() >= -3.0)
                    {
                        if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                        {
                            ply->subYS();
                        }
                        else
                        {
                            deltaY1L = (ply->getYS() - 0.06)- light->getY(0);
                            dist1L = sqrtf((deltaX1L * deltaX1L)+(deltaY1L * deltaY1L));

                            deltaY2L = (ply->getYS() - 0.06)- light->getY(1);
                            dist2L = sqrtf((deltaX2L * deltaX2L)+(deltaY2L * deltaY2L));

                            if (dist1L >= 0.30 + 0.30 && dist2L >= 0.30 + 0.30)
                            {
                                ply->subYS();
                            }
                        }
                    }
                    break;
                }
                break; //of Level 2 inputs
                }
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

void Inputs::keySounds(sounds* snds,int scene)
{
    switch(scene)
    {
        case 4:
        {

            switch(wParam)
            {
                case VK_LEFT:
                case VK_RIGHT:
                case VK_UP:
                case VK_DOWN:
                    //snds->Plays("sounds/forest_walk.mp3");
                    //snds->stopAllSounds();
                    break;
            }
        }
        break;
        case 5:
        {
            case VK_LEFT:
            case VK_RIGHT:
            case VK_UP:
            case VK_DOWN:
                //snds->Plays("sounds/forest_walk.mp3");
                break;
        }
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

