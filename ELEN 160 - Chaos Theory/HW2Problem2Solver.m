function F = HW2Problem2Solver(t, x)
%HW2Problem2Solver Intermediate function for ode45 to solve
%numerically
F = zeros(2, 1);
F(1) = x(1)^2 * x(2) - x(1) / 3 * exp(x(2) - x(1));
F(2) = x(1) - (1 - x(1)^2) * x(2);
end
