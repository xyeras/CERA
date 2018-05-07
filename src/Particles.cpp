#include "Particles.h"
#include <GL/gl.h>

Particles::Particles()
{
    //ctor
}

Particles::~Particles()
{
    //dtor

}
double Particles::dRand()
{
    return (rand()%1000/1000.0);
}

void Particles::drawParticles()
{
    glColor3f(0.0,0.0,1.0);
    glPointSize(3);

    glBegin(GL_POINTS);
       int i =0;
       while(i<NumDrops)
       {
           if(drops[i].alive)
           {
               glVertex3f(drops[i].xpos,drops[i].ypos,-5.0);
           }
           i++;
       }
    glEnd();

}

void Particles::lifeTime()  // setting movement
{
    for(int i=0; i<NumDrops;i++)
    {
       if(drops[i].alive)
       {
          if(drops[i].ypos +GRAVITY*drops[i].mass <0.0)
          {
              drops[i].yDir =-drops[i].yDir/0.3;        // bounce of particles
          }
          else{
            drops[i].yDir += GRAVITY*drops[i].mass;
          }

          drops[i].xpos +=drops[i].xDir;
          drops[i].ypos +=drops[i].yDir;

          if(drops[i].ypos<-5.0 && drops[i].xpos >5.0)
            drops[i].alive =false;
       }


    }
}

void Particles::generateParticles()
{
   int i =0;

   int newDrops = dRand()*60;
    if(NumDrops +newDrops > MAX_DROPS)
        newDrops = MAX_DROPS - NumDrops;

        for(int i= NumDrops; i<NumDrops +newDrops;i++)
        {
           drops[i].alive =true;
           drops[i].xpos = -0.8 +0.1*dRand();
           drops[i].ypos = 0.8 +0.1*dRand();
           drops[i].xDir = 0.0075 +0.025*dRand();
           drops[i].yDir = 0.0;
           drops[i].mass = 0.5 +0.5*dRand();
        }
       NumDrops +=newDrops;

       if(NumDrops >=MAX_DROPS)NumDrops =0;
}
