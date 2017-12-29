function F = ELEN160HW2Problem1Solver(t, x)
%ELEN160HW2Problem1Solver Intermediate function for ode45 to solve
%numerically

F = zeros(2, 1);
F(1) = -1*x(1) + x(2) - 3;
F(2) = x(1)^2 + x(1)*x(2)^2 - 1;

end

