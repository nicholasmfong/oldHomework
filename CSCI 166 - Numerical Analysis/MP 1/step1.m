% file step1.m (name taken from function name)
function [out1] = step1(a)
  for i=1:10,
      out1(i)=a(i)-single(sin(a(i)));
  end;
  return;