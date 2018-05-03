#ifndef ENMS_H
#define ENMS_H

#include <gl/gl.h>
#include <timer.h>

class enms
{
    public:
        enms();
        virtual ~enms();

        void drawEnemy();     // draw objects
        void placeEnemy(float, float,float); // place objects
        void actions(); //movement

        bool isEnemyLive= true; //status of the objects
        GLuint EnemyTex;      // handle Texture
        int EnemyLife;
        float xPos;             //placing objects on x
        float yPos;             //placing objects on y
        float zPos;             //placing objects on z

        float xSize;            // for scaling x
        float ySize;            // for scaling y

        float rotateX;
        float rotateY;
        float rotateZ;
        int frames;
        int action;
        float xmove;
        float ymove;
        timer *TE = new timer();
    protected:

    private:
        float xmin,ymin,xmax,ymax;
};

#endif // ENMS_H
