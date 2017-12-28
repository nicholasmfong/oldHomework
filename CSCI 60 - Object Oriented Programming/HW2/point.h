#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point
{
public:
    // Constructors

    //pre-condition: xval and yval are initial x and y coordinates of this Point with default = (0,0)
    //post-condition: creates a new Point with given coordinates
    Point(double xval = double(), double yval = double());

    //Const Members

    //pre-condition: none
    //post-condition: returns the x coordinate of this Point
    double get_x() const;

    //pre-condition: none
    //post-condition: returns the y coordinate of this Point
    double get_y() const;

    //Mutators

    //pre-condition: none
    //post-condition: sets the x coordinate of this Point to nx
    void set_x(double nx);

    //pre-condition: none
    //post-condition: sets the y coordinate of this Point to nx
    void set_y(double yx);

private:
    //Class Invariants
    //x and y are the x- and y- coordinates of this Point
    double x,y;
};

//input/output operators
std::ostream & operator << (std::ostream &, Point);
std::istream & operator >> (std::istream &, Point &);
bool operator == (Point a, Point b);
#endif // POINT_H
