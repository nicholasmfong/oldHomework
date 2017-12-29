p = 3.8;
iterations = 150;
x1 = logisticMap(0.5, p, iterations);
x2 = logisticMap(0.5-10^-8, p, iterations);
delta = x1-x2;
plot(delta);
title('Plot of differences at p = 3.8');
ylabel('Difference');
xlabel('Iterations (k)');