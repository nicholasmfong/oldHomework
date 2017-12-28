#include <iostream>
#include "namedsquare.h"

using std::cin;
using std::cout;
using std::endl;


int main()
{
  NamedSquare s1(Point(1, 2), 3, "Washington");
  NamedSquare s2(Point(0, 0), 2, "Rittenhouse");
  NamedSquare s3(s1);

  cout << s2 << endl;
  cout << s3 << endl;
  cout << s1.get_center() << endl;
  cout << s1.get_side() << endl;
  cout << s1.get_name() << endl;
  cout << s1.get_area() << endl;
  cout << s1.get_perimeter() << endl;
  cout << s1.get_lower_left() << endl;
  cout << s1.get_upper_right() << endl;

  NamedSquare s4;
  cout << "Enter a named square (center, side, name): "; // Enter -3 1 4 Times
  cin >> s4;
  cout << s4 << endl;

  s4.set_center(Point(-2, -3));
  s4.set_side(1);
  s4.set_name("Tiananman");
  cout << s4 << endl;


  return 0;
}
