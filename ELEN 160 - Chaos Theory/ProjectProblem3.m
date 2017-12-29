format long g;
output = [];
for p = 2.9001:0.0001:3.6000
    xOut = logisticMap(0.5, p, 5000);
    output = [output, xOut];
end
output = output(:,1:end-1); %extra column gets thrown in somehow, this deletes it
final = output(3000:5000,:);
final = roundn(final, 6);
p = seqperiod(final)
% Have to find period doubling manually by looking at p
% Period doubling notes:
% Start of T = 2 at p = 2.9979
% Start of T = 4 at p = 3.4486
% Start of T = 8 at p = 3.5439
% Start of T = 16 at p = 3.5643
% Start of T = 32 at p = 3.5688
% Start of T = 64 at p = 3.5697