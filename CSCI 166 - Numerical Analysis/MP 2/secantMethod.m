%Secant Method root search
p = [3 3.5]; %array of p values with the 2 initial values
i = 2; %start with p0 and p1
maxIteration = 15;
epsilon = 0.0001; %maximum error

while i <= maxIteration
  y = f1(p(i));
  fprintf('iteration %f p=%f y=%f\n', i, p(i), y);
  newval = p(i) - (f1(p(i))*(p(i)-p(i-1))/(f1(p(i)) - f1(p(i-1))));
  if abs(newval - p(i)) < epsilon %check if desired accuracy is met
    fprintf('Answer found:%f with f(x)=%f\n',newval, f1(newval));
    break;
  end;
  p = [p newval];
  ++i;
end;