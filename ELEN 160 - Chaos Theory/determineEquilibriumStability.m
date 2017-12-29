function lambdas = determineEquilibriumStability(F, v, xe)
%Input equations in as F with variables in v and equilibrium xe
% We then solve the Jacobian at xe to get a matrix, then output the
% eigenvalues of that matrix. If all eigenvalues are negative, then xe is
% stable, otherwise it is unstable. See the NewtonsMethod function for
% examples of F and v

    J = jacobian(F, v);
    for i = (1:1:length(v))
        J = subs(J, v(i), xe(i));
    end
    lambdas = eig(J);
    stable = true;
    for i = (1:1:length(lambdas))
        if(real(lambdas(i)) > 0)
            fprintf('Unstable Equilibrium\n\n');
            stable = false;
            break;
        end
    end
    if(stable)
        fprintf('Stable Equilibrium\n\n');
    end
end

