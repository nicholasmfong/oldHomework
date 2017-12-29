% Machine Problem 6 by Nicholas Fong on 3/11/17
% y" = 3y' + x^2
% y' = z
% z' = 3z + x^2
% y(0) = 1, z(0) = 2. Find y(2) using step size h = 0.05

% initialize variables
i = 0;
x = 0;
y = 1;
z = 2;
h = 0.05;

% Use 4th order Runge-Kutta method
while i < 41
  fprintf("Step %d: x = %f, y = %f\n", i, x, y);
  y1 = z;
  z1 = x^2 + 3*z;
  y2 = z + h*z1/2;
  z2 = x^2 + 3*(z + h*z1/2);
  y3 = z + h*z2/2;
  z3 = x^2 + 3*(z + h*z2/2);
  y4 = z + h*z3;
  z4 = x^2 + 3*(z + h*z3);
  y = y + h*(y1 + 2*y2 + 2*y3 + y4)/6;
  z = z + h*(z1 + 2*z2 + 2*z3 + z4)/6;
  x = x + h;
  i++;
end;