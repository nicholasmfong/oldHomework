%file mp1driver.m
%driver for MP1
a = [.05, .04, .03, .02, .01, .001, .0001, .00001, .000001, .0000001];
asing = single(a);
%step 1
out1 = step1(asing);
table1 = [asing; out1];
fprintf(' Step 1, original formula: f(x)= x-sin(x)\n    x         f(x)');
fprintf('\n %9.7f    %14.7e',table1);
fprintf('\n\n');
%step 2
out2 = step2(asing);
table2 = [asing; out2];
fprintf(' Step 2, Maclauren approximation of x-sin(x)\n    x         f(x)');
fprintf('\n %9.7f    %14.7e',table2);
fprintf('\n\n');
%step 3
out3 = step3(asing);
table3 = [asing; out3];
fprintf(' Step 3, Horners approximation of x-sin(x)\n    x         f(x)');
fprintf('\n %9.7f    %14.7e',table3);
fprintf('\n\n');
%step 4
out4 = step4(a);
table4 = [a; out4];
fprintf(' Step 4, double precision: f(x)= x-sin(x)\n    x         f(x)');
fprintf('\n %9.7f    %14.7e',table4);
fprintf('\n\n');

fprintf('The end\n');