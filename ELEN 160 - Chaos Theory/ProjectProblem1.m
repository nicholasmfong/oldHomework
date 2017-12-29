output = [];
for p = 0:0.02:4
    xOut = logisticMap(0.5, p, 700);
    output = [output, xOut];
end
output = output(:,1:end-1); %extra column gets thrown in somehow, this deletes it
final = output(end-100:end,:);
maximums = max(final);
figure;
AX = axes;
plot(maximums);
title('Bifurcation Diagram: Plot of maximums');
xlabel('p');
ylabel('Maximum of last 100 iterations');
oldXAxis = get(AX, 'XTick');
newXAxis = cellstr(num2str(oldXAxis'/50));
set(AX, 'XTickLabel', newXAxis);
% bifurcations after column 50, 150, and 173. 
% Plot representative values for each region
figure;
subplot(2,2,1);
plot(final(:,25));
title('p = 0.6');
subplot(2,2,2);
plot(final(:,100));
title('p = 2');
subplot(2,2,3);
plot(final(:,160));
title('p = 3.2');
subplot(2,2,4);
plot(final(:,185));
title('p = 3.7');