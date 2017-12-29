function F = HW1Prob2Solver(t, x)
A = [4, -3; 6, -5];
F = zeros(2, 1);
F(1) = 4*x(1) - 3*x(2);
F(2) = 6*x(1) - 5*x(2);