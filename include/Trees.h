#ifndef TREES_H
#define TREES_H

typedef struct
{
    float x;
    float y;
    float radius;
}circle;

class Trees
{
    public:
        Trees();
        virtual ~Trees();
        circle trees[3];

        float getRadius(int);
        float getX(int);
        float getY(int);

    protected:

    private:
};

#endif // TREES_H
