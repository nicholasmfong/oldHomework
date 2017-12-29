syms x1 x2;
v = [x1, x2];
F(1) = x1^3 + 5*x1^2*x2 + 8*x1*x2^2 + 4*x2^3 + 2*x1 + 2*x2 + 1;
F(2) = -x1^2 + 2*x1*x2 + 5*x2^2 - 1;

x01 = [1;1];
xe1 = newtonsMethod(F, v, x01);
disp(xe1);
determineEquilibriumStability(F, v, xe1);

 x02 = [15; -15];
 xe2 = newtonsMethod(F, v, x02);
 disp(xe2);
 determineEquilibriumStability(F, v, xe2);