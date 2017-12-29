function x = newtonsMethod(F, v, x0)
%Solve Newton's Method for IC x0 with equations F and variables v
    J = jacobian(F, v);
    x = x0;
    Fx = F; % Fx is F with values inserted
    for i = (1:1:length(v))
        Fx = subs(Fx, v(i), x0(i));
    end
    Fx = transpose(Fx);
    counter = 0;
    while(norm(Fx, Inf) > (10^-6) && counter < 25)
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
        %x = roundn(x, 12);
        counter = counter + 1;
    end
    if(counter == 25)
        fprintf('Did not converge');
    end
    x = double(x);
end