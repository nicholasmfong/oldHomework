output = [];
for p = 0:0.02:4
    xOut = logisticMap(0.5, p, 700);
    output = [output, xOut];
end
output = output(:,1:end-1); %extra column gets thrown in somehow, this deletes it
final = output(end-100:end,:);
% bifurcations after column 50, 150, and 173. 
% Plot representative values for each region
figure;
suptitle('x0 = 0.5');
subplot(2,2,1);
plot(output(1:100,25));
title('p = 0.6');
subplot(2,2,2);
plot(output(1:100,100));
title('p = 2');
subplot(2,2,3);
plot(output(1:100,160));
title('p = 3.2');
subplot(2,2,4);
plot(output(1:100,185));
title('p = 3.7');


% repeat starting at 1.5
output2 = [];
for p = 0:0.02:4
    xOut = logisticMap(1.5, p, 100);
    output2 = [output2, xOut];
end
output2 = output2(:,1:end-1); %extra column gets thrown in somehow, this deletes it
% Plot representative values for each region
figure;
suptitle('x0 = 1.5');
title('x0 = 1.5');
subplot(2,2,1);
plot(output2(1:100,25));
title('p = 0.6');
subplot(2,2,2);
plot(output2(1:100,100));
title('p = 2');
subplot(2,2,3);
plot(output2(1:100,160));
title('p = 3.2');
subplot(2,2,4);
plot(output2(1:100,185));
title('p = 3.7');