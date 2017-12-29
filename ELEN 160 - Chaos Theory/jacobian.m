% returns the Jacobian of a set of functions in a matrix
% f is a vector of functions
%   format [f1, f2, f3...]
% v is a vector of variables/syms
%   format [v1, v2, ...]
function Fn = jacobian(f,v)
    sf = size(f);
    sv = size(v);

    for i = (1:1:sf(2))
        for j = (1:1:sv(2))
            Fn(i,j) = diff(f(i),v(j));
        end
    end
end