% MP 3 Nicholas Fong
% Ax = b, or LUx = b
a1 = [ 3,  2, -3,  1;
       1, -1,  1, -1;
       2, -5,  6,  3;
       6, -4,  4,  3];
b1 = [ 5;
       7;
      10;
      20];
if det(a1) == 0
  printf("Warning: Matrix a1 is singular\n");
end;
[L1, U1] = lu(a1) %factor a1 into triangular matrices
x1Triangle = U1 \ (L1 \ b1);  %solve for x1 using the triangular decomposition
x1Normal = a1 \ b1;
printf("x1 solved using triangular decomposition\n");
x1Triangle
printf("x1 solved using built in Octave solver\n");
x1Normal
printf("----------------------------------------\n");
a2 = [ 1,  1,  1, -1;
       3, -1,  1,  2;
       1, -1,  2,  1;
       2,  3,  1, -1];
b2 = [ 2;
      12;
       9;
       7];
if det(a2) == 0
  printf("Warning: Matrix a2 is singular\n");
end;
[L2, U2] = lu(a2) %factor a2 into triangular matrices
x2Triangle = U2 \ (L2 \ b2);  %solve for x2 using the triangular decomposition
x2Normal = a2 \ b2;
printf("x2 solved using triangular decomposition\n");
x2Triangle
printf("x2 solved using built in Octave solver\n");
x2Normal