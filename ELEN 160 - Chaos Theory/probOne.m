function F = probOne(t, x)
A = [-2, 2; -2, -7];
F = zeros(2, 1);
F(1) = -2*x(1) + 2*x(2);
F(2) = -2*x(1) - 7*x(2);