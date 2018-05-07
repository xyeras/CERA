#ifndef PARTICLES_H
#define PARTICLES_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

#define MAX_DROPS 50000
#define GRAVITY -0.001

using namespace std;


class Particles
{
    public:
        int NumDrops;
        Particles();
        virtual ~Particles();

        typedef struct{

        bool alive;
        float xpos;
        float ypos;
        float zpos;
        float xDir;
        float yDir;
        float mass;

        } particle;

        particle drops[MAX_DROPS];

        void drawParticles();
        void lifeTime();
        void generateParticles();
        double dRand();

    protected:

    private:
};

#endif // PARTICLES_H
