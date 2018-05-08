#include "Inputs.h"
//#include <Trees.h>
//#include <Posts.h>
//#include <math.h>
#include <iostream>
//#include <sounds.h>
using namespace std;
//Trees *tree = new Trees();
//Posts *light = new Posts();
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
            switch(wParam)
            {
                case VK_LEFT:
                    ply->actionTrigger = 1;
                    //ply->setStandDir(1);
                    ply->standDir = 1;              // sets the direction to stand after action


                    break;

                case VK_RIGHT:      // does have a right boundary yet, needs next level goer
                    ply->actionTrigger = 2;
                 //   ply->setStandDir(2);
                    ply->standDir = 2;


                    break;

                case VK_UP:
                    ply->actionTrigger = 3;
              //      ply->setStandDir(3);
                    ply->standDir = 3;

                    break;

                case VK_DOWN:
                    ply->actionTrigger = 4;
               //     ply->setStandDir(4);
                    ply->standDir = 4;

                    break;
                }
    }
                break; // end of Level 1 inputs ----------------------------------------------------------

            case 5:
                {

                    switch(wParam)
                    {
                case VK_LEFT:
                    ply->actionTrigger = 1;
                    //ply->setStandDir(1);
                    ply->standDir = 1;              // sets the direction to stand after action


                    break;

                case VK_RIGHT:
                    ply->actionTrigger = 2;
                    ply->standDir = 2;



                    break;

                case VK_UP:
                    ply->actionTrigger = 3;
                    ply->standDir = 3;

                    break;

                case VK_DOWN:
                    ply->actionTrigger = 4;
                    ply->standDir = 4;

                    break;
                }
                break; //of Level 2 inputs
                }
    }
}


void Inputs::mouseEventDown(player* ply, enms &E)
{
    switch(wParam)
    {
        case MK_LBUTTON:
            ply->actionTrigger = 5;
            float deltaX = ply->getXS() - E.xPos;
            float deltaY = ply->getYS() - E.yPos;
            float dist= sqrtf((deltaX * deltaX)+(deltaY * deltaY));
            cout << "---------------" << endl;
            if (dist < 0.30 + 0.30) // within same space as enemy
            {
                cout << "HIT_______" << endl;
                E.EnemyLife -= 1;
                cout << "-----" << E.EnemyLife << endl;
                if (E.EnemyLife == 0)
                {
                    cout << "Death" << endl;
                  // EVENT HERE FOR DEATH OF ENEMY----------------------------------------------------------
                   E.isEnemyLive = false;
                   // E.EnemyLife = 3;
                }
            }
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
