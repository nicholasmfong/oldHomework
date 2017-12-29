syms p;

% To examine if a system experiences a transcritical birfurcation, examine
% the Jacobian in the neighborhood of p*, where p* = 1
% This code solves for xe, substitutes those values into the Jacobian, and
% examines the eigenvalues to determine stability

p1 = 0.5;
p2 = 1;
p3 = 1.5;

f1 = [1, 2, 2, 1-p1];
f2 = [1, 2, 2, 1-p2];
f3 = [1, 2, 2, 1-p3];

r1 = roots(f1);
r2 = roots(f2);
r3 = roots(f3);

x1 = r1(imag(r1) == 0);
x2 = r2(imag(r2) == 0);
x3 = r3(imag(r3) == 0);

y1 = x1 + x1^2;
y2 = x2 + x2^2;
y3 = x3 + x3^2;

J1 = [-1 - 2*x1, 1; p1, -1 - 2*y1];
J2 = [-1 - 2*x2, 1; p2, -1 - 2*y2];
J3 = [-1 - 2*x3, 1; p3, -1 - 2*y3];

p1
xe1 = [x1; y1]
l1 = eig(J1)
p2
xe2 = [x2; y2]
l2 = eig(J2)
p3
xe3 = [x3; y3]
l3 = eig(J3)