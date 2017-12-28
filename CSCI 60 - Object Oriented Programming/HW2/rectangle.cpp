#include "rectangle.h"              //Rectangle.cpp
Rectangle::Rectangle(Point c, double l, double w){
    _center = c;
    _length = l;    //length is horizontal (x)
    _width = w;     //width is vertical (y)
}
Rectangle::Rectangle(Point lower_left, Point upper_right){
    if(lower_left == upper_right || lower_left.get_x() > upper_right.get_x() || lower_left.get_y() > upper_right.get_y()){
        _center = lower_left;   //tests to see if lower_left is actually lower and left
        _length = 0;           // and if not, it sets the rectangle to be the point at lower_left
        _width = 0;
    }
    else{
        _length = upper_right.get_x()-lower_left.get_x();
        _width = upper_right.get_y()-lower_left.get_y();
        double x,y;
        x = lower_left.get_x() + _length/2.0;
        y = lower_left.get_y() + _width/2.0;
        _center = Point(x,y);
    }
}
double Rectangle::get_length() const{
    return _length;
}
double Rectangle::get_width() const{
    return _width;
}
double Rectangle::get_area() const{
    return _length * _width;
}
double Rectangle::get_perimeter() const{
    return 2*(_length + _width);
}
Point Rectangle::get_lower_left() const{
    double x,y;
    x = _center.get_x()-_length/2;
    y = _center.get_y()-_width/2;
    Point lower_left(x,y);
    return lower_left;
}
Point Rectangle::get_upper_right() const{
    double x,y;
    x = _center.get_x()+_length/2;
    y = _center.get_y()+_width/2;
    Point upper_right(x,y);
    return upper_right;
}
Point Rectangle::get_center() const{
    return _center;
}
void Rectangle::set_length(double l){
    if(l>=0.0){
        _length = l;
    }
}
void Rectangle::set_width(double w){
    if(w>=0.0){
        _width = w;
    }
}
void Rectangle::set_center(Point c){
    _center = c;
}
std::ostream & operator << (std::ostream & os, Rectangle r){
    os<<"[("<<r.get_lower_left()<<"), ("<<r.get_upper_right()<<")]";
    return os;
}
std::istream & operator >> (std::istream & is, Rectangle & r){
    Point center;
    double length,width;
    is>>center>>length>>width;
    r = Rectangle(center,length,width);
    return is;
}
Rectangle operator + (Rectangle a,Rectangle b){
    Point bottom_left = a.get_lower_left(),top_right = a.get_upper_right();     //sets an intermediate bound for the bigger rectangle as a
    if(a.get_lower_left().get_x() > b.get_lower_left().get_x()){  //following 2 statesments are for the lower left bounds of the rectangle
        bottom_left.set_x(b.get_lower_left().get_x());           //if b is left of a, then we resize our bigger rectangle to encompass b
    }
    if(a.get_lower_left().get_y() > b.get_lower_left().get_y()){
        bottom_left.set_y(b.get_lower_left().get_y());             //if b is below a, then we increase our rectangle size to encompass b
    }
    if(a.get_upper_right().get_x() < b.get_upper_right().get_x()){
        top_right.set_x(b.get_upper_right().get_x());            //if b is right of a, then we resize our rectangle to encompass b
    }
    if(a.get_upper_right().get_y() < b.get_upper_right().get_y()){
        top_right.set_y(b.get_upper_right().get_y());           //if b is above a, then we resize our rectangle to encompass b
    }
    Rectangle r(bottom_left,top_right);
    return r;
}
