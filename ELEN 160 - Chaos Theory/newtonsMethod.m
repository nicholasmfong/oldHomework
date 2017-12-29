function x = newtonsMethod(F, v, x0)
%Solve Newton's Method for IC x0 with equations F and variables v
%   e.g. F = [ x2 - x1 - 3, x1^2 + x1*x2^2 - 1]
%   v = [ x1, x2]
%   x0 = [1; 1]
%   where x1 and x2 are declared by: syms x1 x2;
%   and F(1) = -x1 + x2 - 3;
%       F(2) = x1^2 + x1*x2^2 - 1;
    J = jacobian(F, v);
    x = x0;
    Fx = F; % Fx is F with values inserted
    for i = (1:1:length(v))
        Fx = subs(Fx, v(i), x0(i));
    end
    Fx = transpose(Fx);
    counter = 0;
    maxCounter = 25;
    while(norm(Fx, Inf) > (10^-6) && counter < maxCounter)
        JInv = -inv(J);
        Fx = F;
        for i = (1:1:length(v))
            Fx = subs(Fx, v(i), x(i));
        end
        Fx = transpose(Fx);
        for i = (1:1:length(v))
            JInv = subs(JInv, v(i), x(i));
        end
        y = JInv * Fx;
        x = x + y;
        x = double(roundn(x, 12))
        counter = counter + 1;
    end
    if(counter == maxCounter)
        fprintf('Did not converge');
    end
    x = double(x);
end