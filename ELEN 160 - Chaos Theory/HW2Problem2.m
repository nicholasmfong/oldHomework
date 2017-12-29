% Initialize variables
syms x1 x2;
v = [x1, x2];
F(1) = x1^2 * x2 - x1 / 3 * exp(x2 - x1);
F(2) = x1 - (1 - x1^2) * x2;
x01 = [0;0];

% Compute Equilibria and their stability

xe1 = newtonsMethod(F, v, x01);
disp(xe1);
determineEquilibriumStability(F, v, xe1);

x02 = [1;1];
xe2 = newtonsMethod(F, v, x02);
disp(xe2);
determineEquilibriumStability(F, v, xe2);

x03 = [-1;-1];
xe3 = newtonsMethod(F, v, x03);
disp(xe3);
determineEquilibriumStability(F, v, xe3);

x04 = [1;-1];
xe4 = newtonsMethod(F, v, x04);
disp(xe4);
determineEquilibriumStability(F, v, xe4);

% Plot around each equilibria to show their stability properties

xeList = [xe1, xe2, xe3, xe4];
figure;
for i = 1:length(xeList)
    xe = xeList(:,i);
    for adjustment = 1:3
        xTest = xe + (adjustment - 2) * [0.5; 0];
        [t, xTemp] = ode45(@HW2Problem2Solver, [0:0.1:5], xTest);
        k = 3*(i-1) + adjustment;
        subplot(4,3,k);
        plot(t, xTemp(:,1));
    end
end