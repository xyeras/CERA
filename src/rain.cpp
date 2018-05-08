#include "rain.h"

rain::rain()
{
    //ctor
}

rain::~rain()
{
    //dtor
}

void rain::drawParticles()
{
    //glColor3f(0.0,0.0,1.0);
    glPointSize(2);

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

void rain::generateParticles()
{
    int i =0;
    float x,y,z;
   int newDrops = dRand()*60;
   if(NumDrops +newDrops > MAX_DROPS)
        newDrops = MAX_DROPS - NumDrops;

        for(int i= NumDrops; i<NumDrops +newDrops;i++)
        {
           drops[i].alive =true;
           drops[i].xpos = -7+0.1*dRand();
           drops[i].ypos = 7 +0.1*dRand();
           drops[i].xDir = 0.0075 +0.025*dRand();
           drops[i].yDir = 0.0;
           drops[i].mass = 0.5 +0.5*dRand();
        }
       NumDrops +=newDrops;

       if(NumDrops >=MAX_DROPS)NumDrops =0;

}




void rain::lifeTime()
{
    for(int i=0; i<NumDrops;i++)
    {
       if(drops[i].alive)
       {
          if(drops[i].ypos +GRAVITY*drops[i].mass <-3.0)
          {
              drops[i].yDir =drops[i].yDir*2;
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

double rain::dRand()
{
    return (rand()%1000/1000.0);
}

