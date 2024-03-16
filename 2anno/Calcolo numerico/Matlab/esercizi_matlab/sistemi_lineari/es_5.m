close all
clc
clear

n=50;
for i=1:n
    A = flip(diag(ones(i,1)*2)) + flip(diag(ones(i-1,1)*-1,1)) + flip(diag(ones(i-1,1)*-1,-1));
    determinante(i) = det(A);
    condizionamento(i) = cond(A);
end

subplot(1,2,1);
x = 1:n;
plot(x,determinante);
title("determinante");
subplot(1,2,2);
plot(x,condizionamento);
title("condizionamento");
