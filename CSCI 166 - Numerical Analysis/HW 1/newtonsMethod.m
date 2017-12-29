%Newton's Method root search
p = 2 %initial guess
iteration = 1;
maxIteration = 14;
epsilon = 0.0001;

function y = f(x) %replace with whatever function you want to find the root for
  y = power(x,3)-2*power(x,2)-5;
end;
function z = derivative(x) %f'(x)
  z = 3*power(x,2)-4*x;
end;

while iteration <= maxIteration
  y = f(p);
  newval = p - y/derivative(p);
  fprintf('Iteration %f p=%f y=%f\n', iteration, p, y);
  if abs(newval - p) < epsilon
    
    z = f(newval);
    fprintf('Answer found:%f with f(x)=%f\n',newval, z);
    break;
  end;
  p = newval;
  ++iteration;
end;