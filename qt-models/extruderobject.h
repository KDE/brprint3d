#ifndef EXTRUDEROBJECT_H
#define EXTRUDEROBJECT_H


class ExtruderObject
{
public:
    ExtruderObject(int nExtruder, int maxtemp, int mov, int ext, int fan);
    double currTemp;
    void setMaxTemp(int t);
    void setMovSpeed(int s);
    void setExtrusionSpeed(int s);
    void setFanSpeed(int s);
    void setExtrusionQnt(double q);
    int getMaxTemp();
    int getMovSpeed();
    int getExtrusionSpeed();
    int getFanSpeed();
    double getExtrusionQnt();

private:
    int maxTemp;
    int movimentSpeed;
    int extrusionSpeed;
    int fanSpeed;
    int extruderNumber;
    double extrusionQnt;
};

#endif // EXTRUDEROBJECT_H