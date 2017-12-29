function xOut = logisticMap(x0, p, n)
%logisticMap x(k+1) = p*x(k)*(1-x(k)
%   Given x0 and parameter p, we will take n iterations for the formula
%   x(k+1) = p*x(k)*(1-x(k)) and return each x(k) in xOut
    xOut = zeros([n, 1]);    %create array of size n
    xk = x0;
    for i = 1:n
        xOut(i) = xk;
        xk = p * xk * (1 - xk);
    end
end

