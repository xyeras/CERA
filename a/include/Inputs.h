#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include <Model.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <sounds.h>

typedef  struct{
double x;
double y;
double z;
}vec3;



class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void keyPressed(Model *);
        void keyPressed(player *);
        void keyPressed(skyBox *);

        void keyUp(player *);
        void keyUP();
        void keyEnv(parallax *, float); // movements of my background

        void mouseEventDown(player*,double ,double);
        void mouseEventUp();
        void mouseWheel(Model *,double);
        void mouseMove(Model *,double ,double );
        void mouseMove(skyBox *,double ,double );

        double prev_Mouse_X;
        double prev_Mouse_Y;
        bool Mouse_Translate;
        bool Mouse_Roatate;

        void keySound(sounds *);
        vec3 mouseGL(int,int);

        WPARAM wParam;

    protected:

    private:
};

#endif // INPUTS_H
