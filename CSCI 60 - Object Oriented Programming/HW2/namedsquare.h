#ifndef NAMEDSQUARE_H
#define NAMEDSQUARE_H
#include "rectangle.h"
#include <string>

class NamedSquare : public Rectangle
{
public:
    //Constructors
    //pre: s is positive
    //post: creates new NamedSquare centered at c with side s and name n (default constructor)
    NamedSquare(Point c = Point(), double s = double(), std::string n = std::string());

    //pre: none
    //post: creates a new NamedSquare that is a copy of the given NamedSquare(copy constructor)
    NamedSquare(const NamedSquare & source);

    //Const member functions
    //pre: none
    //post: returns the side of this NamedSquare
    double get_side() const;

    //pre: none
    //post: returns the name of this NamedSquare
    std::string get_name() const;

    //Mutators
    //pre: s in positive
    //post: s is the new side of this NamedSquare
    void set_side(double s);

    //pre: none
    //post: n is the new name of this NamedSquare
    void set_name(std::string n);

private:
    //deleted functions
    double get_length() const;
    double get_width() const;
    void set_length(double) const;
    void set_width(double) const;

    //Invariants
    std::string _name;
};

//pre: none
//post: NamedSquare ns is output to the stream os with format [(lower left), (upper right), name]
std::ostream & operator << (std::ostream & os, NamedSquare ns);

//pre:none
//post: a new value of NamedSquare is read in from the stream is in format: center side name
std::istream & operator >> (std::istream & is, NamedSquare & ns);

#endif // NAMEDSQUARE_H
