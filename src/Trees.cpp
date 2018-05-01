#include "Trees.h"

Trees::Trees()
{
    //ctor
  //  trees[0].radius = 0.25;
    trees[0].x = -1.36;
    trees[0].y = 0.4;

 //   trees[1].radius = 0.25;
    trees[1].x = 1.06;
    trees[1].y = 1.32;

 //   trees[2].radius = 0.25;
    trees[2].x = -0.24;
    trees[2].y = -1.50;
}

Trees::~Trees()
{
    //dtor
}

float Trees::getRadius(int i)
{
    return trees[i].radius;
}

float Trees::getX(int i)
{
    return trees[i].x;
}

float Trees::getY(int i)
{
    return trees[i].y;
}
