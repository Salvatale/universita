close all
clear
clc

for n=1:50
A = flip(diag(ones(n,1)*2)+diag(ones(n-1,1)*-1,1)+diag(ones(n-1,1)*-1,-1));
determinante(n) = det(A);
condizionamento(n) = cond(A);
end

plot(1:n,determinante);
hold on
plot(1:n,condizionamento);
legend("determinante","condizionamento");
figure
subplot(1,2,1);
plot(1:n,determinante);
title("determinante");
subplot(1,2,2);
plot(1:n,condizionamento);
title("condizionamento");
