#ifndef PLAYER_H
#define PLAYER_H

#include <Model.h>
#include <gl/gl.h>
#include <textureLoader.h>
# define M_PI           3.14159265358979323846
#include <iostream>
using namespace std;

typedef struct
{
    float x;
    float y;
    float z;
}vec;

class player
{
    public:
        player();
        virtual ~player();

        float scaleSize[3] = {1.0,1.0,1.0};
        vec verticies[4];



        int runspeed;
        int jumpspeed;
        int actionTrigger;
        int inScene;

        void drawPlayer();
        void playerInit(float,float,float,float,int);
        void actions(int);
        void undoAttack();

        void addXS();
        void subXS();
        void addYS();
        void subYS();

        float getXS();
        float getYS();

        void setStandDir(int);

        float xs;
        float ys;
        float zs;

        int standDir;

    protected:

    private:
};

#endif // PLAYER_H
