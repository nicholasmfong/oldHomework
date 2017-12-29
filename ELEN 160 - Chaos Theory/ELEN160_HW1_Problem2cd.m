x0 = [1; 2];
[t, x] = ode45(@HW1Prob2Solver, [0 20], x0);
figure;
plot(x(:,1), x(:,2));
title('Problem 2c:Numerical Solution From 0-20');

[t2, x40] = ode45(@HW1Prob2Solver, [0 40], x0);
figure;
plot(x40(:,1), x40(:,2));
title('Problem 2d:Numerical Solution From 0-40');
