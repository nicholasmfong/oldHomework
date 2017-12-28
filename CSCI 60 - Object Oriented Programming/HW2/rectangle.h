#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "point.h"
#include <iostream>

class Rectangle
{
public:
    //          Constructors

    //pre-condition: l and w are positive
    //post-condition: creates new Rectangle centered at c with length l and width w
    Rectangle(Point c = Point(), double l = double(), double w = double());

    //pre-condition: lower_left must be to the left and below upper_right or they are the same point
    //post-condition: creates a new Rectangle with given corners
    Rectangle(Point lower_left, Point upper_right);

    //          Const Members

    //pre-condition: none
    //post-condition: returns the length of this Rectangle
    double get_length() const;

    //pre-condition: none
    //post-condition: returns the width of this Rectangle
    double get_width() const;

    //pre-condition: none
    //post-condition: returns the area of this Rectangle
    double get_area() const;

    //pre-condition: none
    //post-condition: returns the perimeter of this Rectangle
    double get_perimeter() const;

    //pre-condition: none
    //post-condition: returns the lower left corner of this Rectangle
    Point get_lower_left() const;

    //pre-condition: none
    //post-condition: returns the upper right corner of this Rectangle
    Point get_upper_right() const;

    //pre-condition: none
    //post-condition: returns the center of this Rectangle
    Point get_center() const;

    //          Mutators

    //pre-condition: l is positive
    //post-condition: l is the new length of this Rectangle; its center and width are unchanged
    void set_length(double l);

    //pre-condition: w is positive
    //post-condition: w is the new width of this Rectangle; its center are length are unchanged
    void set_width(double w);

    //pre-condition: none
    //post-condition: c is the new center of this Rectangle; its length and width are unchanged
    void set_center(Point c);

private:
    //Class Invariants
    //_center, _length, _width are the center, length, and width of this Rectangle respectively
    Point _center;
    double _length;
    double _width;
};

//              input/output operators

//pre-condition: none
//post-condition: Rectangle r is output to stream os in the following format: [(lower left), (upper right)]
std::ostream & operator << (std::ostream & os, Rectangle r);

//pre-condition: none
//post-condition: a new value of Rectangle r is read from stream is in the following format: center length width
std::istream & operator >> (std::istream & is, Rectangle & r);

//pre-condition: none
//post-condition: returns the smallest rectangle containing both a and b
Rectangle operator + (Rectangle a, Rectangle b);

#endif // RECTANGLE_H
