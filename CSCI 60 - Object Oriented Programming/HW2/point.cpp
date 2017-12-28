#include "point.h"      //point.cpp
Point::Point(double xval, double yval){
    x = xval;
    y = yval;
}
double Point::get_x() const{
    return x;
}
double Point::get_y() const{
    return y;
}
void Point::set_x(double nx){
    x = nx;
}
void Point::set_y(double ny){
    y = ny;
}
std::ostream & operator << (std::ostream & os, Point p){
    os << "(" << p.get_x() << ", " << p.get_y() << ")";
    return os;
}
std::istream & operator >> (std::istream & is, Point & p){
    double x,y;
    is >> x >> y;
    p = Point(x,y);
    return is;
}
bool operator == (Point a,Point b){
    if(a.get_x()==b.get_x() && a.get_y()==b.get_y()){
        return true;
    }
    else{
        return false;
    }
}
