#ifndef BEDOBJECT_H
#define BEDOBJECT_H


class BedObject
{
public:
    BedObject(int x, int y, int z);
    double currTemp;
    int getX();
    int getY();
    int getZ();
    double getDesireTemp();
    void setDesireTemp(double t);

private:
    double desireTemp;
    int areaX;
    int areaY;
    int areaZ;
};

#endif // BEDOBJECT_H
