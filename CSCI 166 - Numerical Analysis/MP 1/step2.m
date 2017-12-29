% file step2.m (name taken from function name)
function [out2] = step2(a)
  for i=1:10,
      out2(i)=single(power(a(i),3)/factorial(3))-single(power(a(i),5)/factorial(5))+single(power(a(i),7)/factorial(7))-single(power(a(i),9)/factorial(9));
  end;
  return;