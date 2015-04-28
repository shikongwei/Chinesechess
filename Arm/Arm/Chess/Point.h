#ifndef POINT_H
#define POINT_H
class OurPoint
{
public:
    int x;
    int y;
    OurPoint()
    {

    }
    OurPoint(int x_l,int y_l)
    {
        x=x_l;
        y=y_l;
    }
};
class OurPointf
{
public:
    float x;
    float y;
    OurPointf()
    {

    }
    OurPointf(float x_l,float y_l)
    {
        x=x_l;
        y=y_l;
    }
};

#endif // POINT_H
