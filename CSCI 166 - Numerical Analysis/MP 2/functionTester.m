%evaluates an input function every x units
lowerBound = -10;
upperBound = 10;
xValue = lowerBound;
step = 0.5; %space between evaluated locations
results = []; %array to hold the results
while xValue <= upperBound %evaluate the function at various points
  y = f1(xValue); %f1 is a separate function file
  fprintf('At x = %f, y = %f\n', xValue, y);
  results = [results f1(xValue)]; %append the result in an array.
  xValue += step;
end;