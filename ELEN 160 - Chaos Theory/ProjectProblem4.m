output = [];
for p = 3.820160:0.000001:3.820180
    xOut = logisticMap(0.5, p, 500);
    figure;
    plot(xOut);
    title(p);
    output = [output, xOut];
end
output = output(:,1:end-1); %extra column gets thrown in somehow, this deletes it
% 3.82017
% 3.82016
% 3.82013
