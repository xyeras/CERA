#ifndef FIRE_H
#define FIRE_H


class fire
{
    public:
        fire();
        virtual ~fire();

        void drawFire();         //draw object
        void placeFire(float,float,float);   // place object

        bool isObjectLive = true;     //status of the objects
        GLuint objectTex;            // handle Texture

        float xPos;                 // placing objects on x
        float yPos;                 // placing objects on y
        float zPos;                 // placing objects on z

        float xSize;                // for scaling x
        float ySize;                // for scaling y

        float rotateX;
        float rotateY;
        float rotateZ;

    protected:

    private:
};

#endif // FIRE_H
