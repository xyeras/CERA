#include "Posts.h"

Posts::Posts()
{
    //ctor
    lights[0].x = -3.78;
    lights[0].y = 1.52;

    lights[1].x = 2.52;
    lights[1].y = 1.52;
}

Posts::~Posts()
{
    //dtor
}

float Posts::getRadius(int i)
{
    return lights[i].radius;
}

float Posts::getX(int i)
{
    return lights[i].x;
}

float Posts::getY(int i)
{
    return lights[i].y;
}
