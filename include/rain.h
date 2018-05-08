#ifndef RAIN_H
#define RAIN_H

#include <gl/gl.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#define MAX_DROPS 50000
#define GRAVITY -0.00015


class rain
{
    public:
        int NumDrops;
        rain();
        virtual ~rain();
        typedef struct
        {
            bool alive;
            float xpos,ypos,zpos;
            float xDir,yDir;
            float mass;

        }particle;
        float zoom=-40.0;
        particle drops[MAX_DROPS];
        void drawParticles();
        void generateParticles();
        void lifeTime();
        double dRand();
    protected:

    private:
};

#endif // RAIN_H
