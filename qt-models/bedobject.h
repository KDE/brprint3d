#ifndef BEDOBJECT_H
#define BEDOBJECT_H


class bedObject
{
public:
    bedObject(int x, int y, int z);

    int getX();
    int getY();
    int getZ();
    double getDesireTemp();
    double getCurrTemp();
    void setDesireTemp(double t);
    void setCurrTemp(double t);

private:

    double currTemp;
    double desireTemp;
    int areaX;
    int areaY;
    int areaZ;
};

#endif // BEDOBJECT_H
