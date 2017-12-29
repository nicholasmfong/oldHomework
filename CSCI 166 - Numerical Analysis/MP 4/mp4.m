% MP 4 by Nicholas Fong on 2-16-17 for CSCI 166
y1 = [1, 4, 0, 4, 4, 0, 4, -6]; % y1 = x^7 + 4x^6 + 4x^4 + 4x^3 + 4x - 6
y2 = [1, -5, 2, 22, -31, -5, 28, -12]; % y2 = x^7 - 5x^6 + 2x^5 + 22x^4 - 31x^3 - 5x^2 + 28x - 12
companion1 = compan(y1);  % get the companion matrices
companion2 = compan(y2);
eigenvalues1 = eig(companion1); % get the eigenvalues of the companion matrices
eigenvalues2 = eig(companion2); % which are the roots of the polynomials
% output the results
fprintf("y1 = x^7 + 4x^6 + 4x^4 + 4x^3 + 4x - 6\nIts companion matrix is\n");
disp(companion1);
fprintf("The eigenvalues of the companion matrix, or the roots of y1, are\n");
display(eigenvalues1);  % display seems to be the same as disp except it adds a newline at the end
fprintf("y2 = x^7 - 5x^6 + 2x^5 + 22x^4 - 31x^3 - 5x^2 + 28x - 12\nIts companion matrix is\n");
disp(companion2);
fprintf("The eigenvalues of the companion matrix, or the roots of y2, are\n");
display(eigenvalues2);