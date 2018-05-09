#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include <Model.h>
#include <parallax.h>
#include <player.h>
#include <sounds.h>
#include <enms.h>
#include <textureLoader.h>
#include <GLScene.h>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void keyPressed(Model *);
        void keyPressed(player *);
        void keyUP(player *);
        void keyEnv(parallax *,float); // movements of my background

        bool mouseEventDown(player *,enms&);
        void mouseEventUp(player *);
        void mouseWheel(Model *,double);
        void mouseMove(Model *,double ,double );
        void keySounds(sounds*,int);
        void mouseEventDown(sounds*);

        double prev_Mouse_X;
        double prev_Mouse_Y;
        bool Mouse_Translate;
        bool Mouse_Roatate;

        WPARAM wParam;

    protected:

    private:
};

#endif // INPUTS_H
