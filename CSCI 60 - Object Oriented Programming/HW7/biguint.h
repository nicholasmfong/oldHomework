#ifndef BIGUINT_H
#define BIGUINT_H       //biguint.h
#include <QString>
class biguint
{
public:
    // TYPES and CONSTANTS
    typedef std::size_t size_type;

    //Constructors / Destructors
    //pre: none
    //post:creates a biguint whose value is n and whose capacity is at least m (default n = 0, m = 1)
    //Note:a decimal integer n requires log(n+1)/log(10) (rounded up) digits
    biguint(unsigned int n = 0, size_type m = 1);

    // pre: none
    // post: creates a biguint whose digits are given in a string s
    //       rightmost digit of s corresponds to the least significant
    //       digit
    biguint (const char s[], size_type m = 1);
    biguint (const std::string & s, size_type m = 1);

    // pre: none
    // post: destroys this biguint
    ~biguint();

    // assigment operator
    void operator =(const biguint & b);

    // pre: none
    // post: returns the number of digits (no leading 0’s) in this biguint
    size_type digits() const;

    // division and remainder operators
    // pre: b != 0
    // post: returns the quotient/remainder of this biguint divided by divisor
    // NOTE: also implement the corresponding nonmember operators / and %
    void operator /= (const biguint & divisor);
    void operator %= (const biguint & divisor);

    // pre-increment/decrement operators
    // pre: none
    // post: this biguint has been incremented/decremented by 1
    // return value is the NEW value
    biguint operator ++();
    biguint operator --();

    // post-increment/decrement operators
    // pre: none
    // post: this biguint has beeen incremented/decremented by 1
    // return value is the ORIGINAL value
    biguint operator ++(int);
    // there is actually no input paramenter
    // int is used to distinguish between post-increment from pre-increment (which has no input parameters)
    biguint operator --(int);

    // CONSTANT FUNCTIONS

    // pre: none
    // post: resizes this biguint to given size
    void resize(size_type length = 1);

    // pre: pos < CAPACITY
    // post: returns the (pos+1)^st digit from the right of this biguint
    size_type operator [](size_type pos) const;

    // pre: none
    // post: return 0 if n == this biguint
    //             -1 if n > this biguint
    //              1 if n < this biguint
    int compare(const biguint & n) const;

    // pre: none
    // post: b has been added to this biguint
    //       overflow digit will be thrown away, if any
    void operator +=(const biguint &b);

    // pre: none
    // post: if b > this biguint, then this biguint is reset to 0
    //       else b is subtracted from this biguint
    void operator -=(const biguint & b);

    // pre: d <= 9;
    // post: this biguint has been multiplied by d
    void operator *= (size_type d);

    // pre: none
    // post: this biguint is multiplied with another biguint with overflow digits discarded
    void operator *= (const biguint & b);

    // pre: none
    // post: digits of this biguint has been left shifted by 1 position
    //       the former most significant digit is discarded
    //       the new least significiant digit is 0
    void ls();

    // pre: none
    // post: returns a string of this biguint
    QString toQString();

    // pre: none
    // post: returns the CAPACITY of this biguint
    size_type get_CAPACITY() const;

    //MUTATORS
    // pre: none
    // post: changes the CAPACITY of this biguint to m
    void set_CAPACITY(size_type m);
private:
    size_type *data;
    size_type CAPACITY;
    //data[0...capacity-1] is a dynamic array
    //data[i] corresponds to the coefficient of 10^i for 0 <= i < capacity
};
//NON-MEMBER FUNCTIONS
std::ostream & operator <<(std::ostream & os, const biguint &);
std::istream & operator >>(std::istream & is, biguint &);
biguint operator + (const biguint &, const biguint &);
biguint operator - (const biguint &, const biguint &);
biguint operator * (const biguint &, biguint::size_type);
biguint operator / (const biguint &, const biguint &);
biguint operator % (const biguint &, const biguint &);
bool operator < (const biguint &, const biguint &);
bool operator <= (const biguint &, const biguint &);
bool operator == (const biguint &, const biguint &);
bool operator != (const biguint &, const biguint &);
bool operator > (const biguint &, const biguint &);
bool operator >= (const biguint &, const biguint &);
#endif // BIGUINT_H
