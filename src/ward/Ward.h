#ifndef WARD_H
#define WARD_H

struct Point
{
    double x;
    double y;
};

class Ward
{
    protected:
        char name;
        Point entry;
        Point exit;
        Point top_left;
        Point top_right;
        Point low_left;
        Point low_right;
    public:
        Ward();
        // ~Ward();
        char getName();

        Point getEntry();

        Point getExit();

        Point getTopLeft();

        Point getTopRight();

        Point getLowRight();

        Point getLowLeft();

        void setName(char name);

        void setEntry(double x, double y);

        void setExit(double x, double y);

        void setTopLeft(double x, double y);

        void setTopRight(double x, double y);

        void setLowRight(double x, double y);

        void setLowLeft(double x, double y);

        // virtual void build();
};


#endif