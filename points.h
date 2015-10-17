#ifndef POINTS_H
#define POINTS_H
#include <QVector>
#include <iostream>

class Points
{
private:

        float x;
        float y;
        float z;

public:
    Points();
    ~Points();
    void addPoint(float x, float y, float z) throw (QString);
    void getPoint(float *x,float *y, float *z) throw (QString);
};

#endif // POINTS_H
