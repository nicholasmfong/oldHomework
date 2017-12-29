%Nicholas Fong CSCI 166 MP 5 3/5/17

%data
x1 = [0,0.15,0.31,0.5,0.6,0.75];
x1New = 0:0.05:0.75;
y1 = [1,1.004,1.031,1.117,1.223,1.422];

x2 = [4,4.2,4.5,4.7,5.1,5.5,5.9,6.3,6.8,7.1];
x2New = 4:0.05:7.1;
y2 = [102.56,113.18,130.11,142.05,167.53,195.14,224.87,256.73,299.5,326.72];

x3 = [0.2,0.3,0.6,0.9,1.1,1.3,1.4,1.6];
x3New = 0.2:0.05:1.6;
y3 = [0.050446,0.098426,0.33277,0.7266,1.0972,1.5697,1.8487,2.5015];

%does the regression and plots it
function regression(x,xNew,y)
  linRegCoefficients = polyfit(x,y,1);
  quadRegCoefficients = polyfit(x,y,2);
  fprintf("x =");
  disp(x);
  fprintf("y =");
  disp(y);
  fprintf("linear regression coefficients =");
  disp(linRegCoefficients);
  fprintf("quadratic regression coefficients =");
  disp(quadRegCoefficients);
  yNewLinReg = polyval(linRegCoefficients, xNew);
  yNewQuadReg = polyval(quadRegCoefficients, xNew);
  plot(x,y,'o',xNew,yNewLinReg,xNew,yNewQuadReg);
end;

%run everything
figure(1);
fprintf('Figure 1:\n');
regression(x1,x1New,y1);
figure(2);
fprintf('\nFigure 2:\n');
regression(x2,x2New,y2);
figure(3);
fprintf('\nFigure 3:\n');
regression(x3,x3New,y3);