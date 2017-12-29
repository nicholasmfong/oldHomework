%False Position Method root search
%bracketing method using the secant line
a = 0; %lower bound
b = 2; %upper bound
p = [a b]; %array of p values with the 2 initial values
i = 2; %start with p0 and p1
maxIteration = 25;
epsilon = 0.0001;

function y = f(x) %replace with whatever function you want to find the root for
  y = power(x,2)-2;
end;

while i <= maxIteration
  y = f(p(i));
  fprintf('iteration %f [a,b]=[%f,%f] p=%f y=%f\n', i, a, b, p(i), y);
  newval = b - f(b)*(b-a)/(f(b) - f(a));
  if abs(newval - p(i)) < epsilon
    fprintf('Answer found:%f with f(x)=%f\n',newval, f(newval));
    break;
  end;
  
  if f(newval) > 0
    b = newval;
  else
    a = newval;
  end;
  p = [p newval];
  ++i;
end;