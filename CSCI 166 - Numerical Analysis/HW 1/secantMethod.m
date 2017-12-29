%Secant Method root search
p = [1 4]; %array of p values with the 2 initial values
i = 2 %start with p0 and p1
maxIteration = 14;
epsilon = 0.0001;

function y = f(x) %replace with whatever function you want to find the root for
  y = power(x,3)-2*power(x,2)-5;
end;

while i <= maxIteration
  y = f(p(i));
  fprintf('iteration %f p=%f y=%f\n', i, p(i), y);
  newval = p(i) - (f(p(i))*(p(i)-p(i-1))/(f(p(i)) - f(p(i-1))));
  if abs(newval - p(i)) < epsilon
    fprintf('Answer found:%f with f(x)=%f\n',newval, f(newval));
    break;
  end;
  p = [p newval];
  ++i;
end;