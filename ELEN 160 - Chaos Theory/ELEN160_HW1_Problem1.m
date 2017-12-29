x0 = [1; 1];
[t, x] = ode45(@probOne, [0 2], x0);
plot(x(:,1), x(:,2));
title('Problem 1:Numerical Solution From Matlab');

analytic = [];
for elm = t
    temp = -exp(-6*elm)*[1, -2] - exp(-3*elm)*[-2, 1];
    analytic = [analytic, temp];
end

figure;
plot(analytic(:,1), analytic(:,2));
title('Problem 1:Analytic Solution From Matlab');