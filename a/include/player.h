#ifndef PLAYER_H
#define PLAYER_H

#include<Model.h>
#include<gl/gl.h>
#include<textureLoader.h>

typedef struct
{
   float x;
   float y;
   float z;
}vec;

class player:public Model
{
    public:
        player();
        virtual ~player();

        float scalesize[3]={1.0,1.0,1.0};
        vec verticies[4];

        double spin;
        int runspeed;
        int jumpspeed;
        int actionTrigger;

        void drawPlayer();
        void playerInit();
        void actions(int);

    protected:

    private:
};

#endif // PLAYER_H
