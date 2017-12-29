%bisection root search
a = 1; %lower bound
b = 2; %upper bound
p = a + (b-a)/2;
iteration = 1;
maxIteration = 14;
function y = f(x) %replace with whatever function you want to find the root for
  y = power(x,3)-x-1;
end;
while iteration <= maxIteration
  y = f(p);
  fprintf('Iteration %f a=%f b=%f p=%f y=%f   ', iteration, a, b, p, y);
  if y < 0
    a = p;
  elseif y > 0
    b = p;
  else %in the rare chance that your bisection finds the actual root
    fprintf('Answer = %f', p);
    break;
  end;
  p = a + (b-a)/2
  ++iteration;
end;