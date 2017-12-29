% Initialize variables
syms x1 x2 x3 p;
v = [x1, x2, x3];
F(1) = 2*x2^2 + p*x1*x2 - x3;
F(2) = x1*(x2+1) - p*x2;
F(3) = -3*x2^2 + 2*p*x1 + 2*x3 + p;

F = subs(F, p, 0)

x01 = [0;0;0];

% Compute Equilibria and their stability

xe1 = newtonsMethod(F, v, x01);
disp(xe1);
determineEquilibriumStability(F, v, xe1);

% x02 = [-1; 0; 0.5];
% xe2 = newtonsMethod(F, v, x02);
% disp(xe2);
% determineEquilibriumStability(F, v, xe2);

% Plot around each equilibria to show their stability properties
% 
% xeList = [xe1, xe2, xe3, xe4];
% figure;
% for i = 1:length(xeList)
%     xe = xeList(:,i);
%     for adjustment = 1:3
%         xTest = xe + (adjustment - 2) * [0.5; 0];
%         [t, xTemp] = ode45(@HW2Problem2Solver, [0:0.1:5], xTest);
%         k = 3*(i-1) + adjustment;
%         subplot(4,3,k);
%         plot(t, xTemp(:,1));
%     end
% end