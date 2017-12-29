% file step3.m (name taken from function name)
function [out3] = step3(a)
  for i=1:10,
      out3(i)=single((single((single((single(-power(a(i),2)/factorial(9))+1/factorial(7))*power(a(i),2))-1/factorial(5))*power(a(i),2))+1/factorial(3))*power(a(i),2));
  end;
  return;