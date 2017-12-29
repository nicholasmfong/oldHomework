function void = ELEN160HW2Problem1Plot()
%ELEN160HW2Problem1Plot Plots near the equilibirum points and generates a graph
%   Detailed explanation goes here

syms x1 x2;
v = [x1 x2];
f(1) = -x1 + x2 - 3;
f(2) = x1^2 + x1*x2^2 -1;

xe1 = [0.1028; 3.1028];
xe2 = [-5.2491; -2.2491];
xe3 = [-1.8536; 1.1464];
xeList = [xe1, xe2, xe3];
xValues(1:21, 1:9) = 0;
figure;
for i = 1:length(xeList)
    xe = xeList(:,i);
    for adjustment = 1:3
        xTest = xe + (adjustment - 2) * [0.5; 0];
        [t, xTemp] = ode45(@ELEN160HW2Problem1Solver, [0:0.1:5], xTest);
        k = 3*(i-1) + adjustment;
        %xValues(:,k) = xTemp(:,1);
        subplot(3,3,k);
        %plot(t, xValues(:,k));
        plot(t, xTemp(:,1));
    end
end

