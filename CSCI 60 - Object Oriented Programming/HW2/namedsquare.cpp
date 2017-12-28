#include "namedsquare.h"        //NamedSquare.cpp
#include "assert.h"
#include <string>

NamedSquare::NamedSquare(Point c, double s, std::string n):Rectangle(c,s,s), _name(n){
    assert(s>=0);
}
NamedSquare::NamedSquare(const NamedSquare &source):Rectangle(source.Rectangle::get_center(),source.get_side(),source.get_side()), _name(source._name)
{}
double NamedSquare::get_side() const{
    return Rectangle::get_length();
}
std::string NamedSquare::get_name() const{
    return _name;
}
void NamedSquare::set_side(double s){
    if(s>=0){
        Rectangle::set_length(s);
        Rectangle::set_width(s);
    }
}
void NamedSquare::set_name(std::string n){
    _name = n;
}
std::ostream & operator << (std::ostream & os, NamedSquare ns){
    os<<"["<<ns.get_lower_left()<<", "<<ns.get_upper_right()<<","<<ns.get_name()<<"]";
    return os;
}
std::istream & operator >> (std::istream & is, NamedSquare & ns){
    Point c;
    double s;
    std::string n;
    is>>c>>s>>n;
    ns = NamedSquare(c,s,n);
    return is;
}
