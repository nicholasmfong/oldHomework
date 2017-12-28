#include "biguint.h"
#include <cassert>
#include <cctype>       //biguint.cpp
#include <QString>
#include <cmath>

//CONSTRUCTORS

biguint::biguint(unsigned int n, size_type m){
    if(ceil(log(n+1.0)/log(10)) > m){
        m = ceil(log(n+1.0)/log(10));
    }
    CAPACITY = m;
    data = new size_type[CAPACITY];
    std::fill(data, data+CAPACITY, 0);
    size_type i(0);
    while (n > 0){
        data[i] = n % 10;
        ++i;
        n /= 10;
    }
}
biguint::biguint(const std::string &s,size_type m){
    if(s.size() > m){
        m = s.size();
    }
    CAPACITY = m;
    data = new size_type[CAPACITY];
    std::fill(data, data+CAPACITY, 0);
    for (size_type i = 0; i < m; ++i)
    {
        assert(isdigit(s[i]));
        data[m-1-i] = s[i] - '0';
    }
}
biguint::biguint(const char s[],size_type m)
    : biguint(std::string(s),m)
{
}
biguint::~biguint(){
    delete [] data;
};

//CONSTANT MEMBER FUNCTIONS

biguint::size_type biguint::operator[](size_type pos) const{
    assert(pos < CAPACITY);
    return data[pos];
}
void biguint::operator =(const biguint & b){
    if (this == &b) // self-assignment
        return;
    CAPACITY = b.CAPACITY;
    delete [] data;
    data = new size_type[CAPACITY];
    for(size_type i = 0; i < CAPACITY; i++){
        data[i] = b.data[i];
    }
}
void biguint::resize(size_type length){
    if(length < digits() || length == CAPACITY){
        return;
    }
    size_type *new_data = new size_type[length];
    std::copy(data,data+digits(),new_data);
    delete [] data;
    data = new_data;
    CAPACITY = length;
}
void biguint::operator +=(const biguint & b){
    size_type carry(0);
    biguint copy = b;
    size_type new_size = std::max(digits(),b.digits()) + 1;
    resize(new_size);
    copy.resize(new_size);
    for (size_type i = 0; i < CAPACITY; ++i){
        size_type sum = carry + data[i] + copy.data[i];
        data[i] = sum % 10;
        carry = sum / 10;
    }
}
int biguint::compare(const biguint &n) const{
    size_type leading_digit = n.CAPACITY-1;     //this part is for the possibly different sized biguints
    while(n.data[leading_digit] == 0 && leading_digit > 0){
        leading_digit -= 1;
    }
    if(leading_digit > (CAPACITY - 1)){
        return -1;
    }
    if(CAPACITY > n.CAPACITY){
        size_type this_leading = CAPACITY - 1;
        while(this_leading == 0 && this_leading > (n.CAPACITY-1)){
            this_leading -= 1;
        }
        if(this_leading > (n.CAPACITY-1)){
            return 1;
        }
    }
    for (int i = n.CAPACITY -1; i >= 0; --i){     //normal part
        if (data[i] < n.data[i])
            return -1;
        if (data[i] > n.data[i])
            return 1;
    }
    return 0;
}
void biguint::operator -=(const biguint & b){
    if (compare(b) == -1){
        std::fill(data, data+CAPACITY, 0);
        return;
    }
    size_type borrow(0);
    for (size_type i = 0; i < CAPACITY; ++i){
        size_type t = b.data[i] + borrow;
        if (data[i] >= t){
            data[i] -= t;
            borrow = 0;
        }
        else{
            data[i] += 10;
            data[i] -= t;
            borrow = 1;
        }
    }
}
void biguint::operator *=(size_type d){
    assert(d <= 9);
    size_type carry(0);
    if(data[CAPACITY-1] != 0){
        CAPACITY++;
        resize(CAPACITY);
    }
    for (size_type i = 0; i < CAPACITY; ++i){
        size_type sum = carry + data[i] * d;
        data[i] = sum % 10;
        carry = sum/10;
    }
}
void biguint::operator *=(const biguint & b){
    biguint ans("0",1);
    for(int i = CAPACITY-1; i >= 0; i--){
        ans.ls();
        ans += (b*data[i]);
    }
    if(ans.get_CAPACITY() < CAPACITY){
        ans.resize(CAPACITY);
    }
    for(size_type j = 0; j < CAPACITY; ++j){    //stores the answer
        data[j] = ans[j];
    }
}
void biguint::ls(){
    this->resize(CAPACITY+1);
    for (size_type i = CAPACITY -1; i > 0; i--){
        data[i] = data[i-1];
    }
    data[0] = 0;
}
//Easter Egg for Brandon Young: Kirby Fight  (>*_*)>   Q(@_@Q)

//Who will win? You decide! Circle the one who will win)
QString biguint::toQString(){
    QString x;
    int size = CAPACITY-1;
    while(size > 0 && data[size] == 0){
        --size;
    }
    while(size >= 0){
        x += data[size] + '0';
        --size;
    }
    return x;
}
biguint::size_type biguint::get_CAPACITY() const{
    return CAPACITY;
}
void biguint::set_CAPACITY(size_type m){
    CAPACITY = m;
    resize(CAPACITY);
}
biguint::size_type biguint::digits() const{
    size_type count = CAPACITY-1;
    while(data[count] == 0 && count > 0){
        count--;
    }
    return (count+1);
}
biguint biguint::operator ++(){
    *this += 1;
    return *this;
}
biguint biguint::operator ++(int){
    biguint copy = *this;
    *this += 1;
    return copy;
}
biguint biguint::operator --(){
    *this -= 1;
    return *this;
}
biguint biguint::operator --(int){
    biguint copy = *this;
    *this -= 1;
    return copy;
}
void biguint::operator /=(const biguint & divisor){
    biguint remainder("0", divisor.digits());
    biguint quotient("0", digits());
    for (int i = digits()-1; i >= 0; --i){
    remainder.ls();
    remainder.data[0] = data[i];
    size_type count(0);
    while (remainder >= divisor){
    ++count;
    remainder -= divisor;
    }
    quotient.data[i] = count;
    }
    CAPACITY = digits()-divisor.digits()+1;
    quotient.resize(CAPACITY);
    delete [] data;
    *this = quotient;
}
void biguint::operator %=(const biguint & divisor){
    biguint remainder("0", divisor.digits());
    biguint quotient("0", digits());
    for (int i = digits()-1; i >= 0; --i){
    remainder.ls();
    remainder.data[0] = data[i];
    size_type count(0);
    while (remainder >= divisor){
    ++count;
    remainder -= divisor;
    }
    quotient.data[i] = count;
    }
    CAPACITY = divisor.digits();
    remainder.resize(CAPACITY);
    delete [] data;
    *this = remainder;
}

//NON_MEMBER FUNCTIONS

std::ostream & operator << (std::ostream &os, const biguint & b){
    biguint::size_type i = b.digits()-1;
    while (i > 0){
        os << b[i];
        i--;
    }
    os << b[0];
   return os;
}
std::istream & operator >>(std::istream & is, biguint & b){
    std::string s;
    is >> s;
    b = biguint(s,1);
    return is;
}
biguint operator + (const biguint &a, const biguint &b){
    biguint ans(a);
    ans += b;
    return ans;
}
biguint operator - (const biguint & a, const biguint & b){
    biguint ans(a);
    ans -= b;
    return ans;
}
biguint operator * (const biguint & b, biguint::size_type d){
    biguint ans(b);
    ans *= d;
    return ans;
}
biguint operator / (const biguint & a, const biguint & b){
    biguint ans(a);
    ans /= b;
    return ans;
}
biguint operator % (const biguint & a, const biguint & b){
    biguint ans(a);
    ans %= b;
    return ans;
}
bool operator < (const biguint & a, const biguint & b){
    if(a.compare(b) == -1){
        return true;
    }
    return false;
}
bool operator > (const biguint & a, const biguint & b){
    if(a.compare(b) == 1){
        return true;
    }
    return false;
}
bool operator != (const biguint & a, const biguint & b){
    if(a.compare(b) == 0){
        return false;
    }
    return true;
}
bool operator == (const biguint & a, const biguint & b){
    if(a.compare(b) == 0){
        return true;
    }
    return false;
}
bool operator >= (const biguint & a, const biguint & b){
    if(a.compare(b) == -1){
        return false;
    }
    return true;
}
bool operator <= (const biguint & a, const biguint & b){
    if(a.compare(b) == 1){
        return false;
    }
    return true;
}
