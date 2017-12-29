y = [1, 2];
analytic = [];
t = transpose([0:0.01:1]);
for elm = t
    temp = exp(-6*elm)*y;
    analytic = [analytic, temp];
end

figure;
plot(analytic(:,1), analytic(:,2));
title('Problem 2b:Analytic Solution From Matlab');