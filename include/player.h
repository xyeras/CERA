#ifndef PLAYER_H
#define PLAYER_H

#include <Model.h>
#include <gl/gl.h>
#include <textureLoader.h>

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

        void drawPlayer();
        void playerInit();
        void actions(int);

        void addXS();
        void subXS();
        void addYS();
        void subYS();

        float xs;
        float ys;
        float zs;

    protected:

    private:
};

#endif // PLAYER_H
