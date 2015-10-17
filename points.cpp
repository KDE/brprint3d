/* This file is a class of points in X,Y and Z Axis*/
#include "points.h"

Points::Points()
{

}
Points::~Points()
{
    delete this;
}

void Points::addPoint(float x, float y, float z) throw (QString)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Points::getPoint(float *x, float *y, float *z) throw (QString)
{
    (*x) = this->x;
    (*y) = this->y;
    (*z) = this->z;
}


