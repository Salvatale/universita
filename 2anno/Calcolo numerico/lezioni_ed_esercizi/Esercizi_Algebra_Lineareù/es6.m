close all
clear
clc

n = 1000;
A = hilb(n);
B = rand(n);

%parte a
disp('parte a');
x = ones(n,1);
b = A*x;
y = ones(n,1);
c = B*y;
%parte b e c
disp('parte b e c');
x1 = A\b;
y1 = B\c;
errore_relativo_x = norm(x-x1,"inf")/norm(ones(n,1),"inf")
errore_relativo_y = norm(y-y1,"inf")/norm(ones(n,1),"inf")
condizionamento_y = cond(A,"inf")

%parte d
for i=2:50
    H = hilb(i);
    condizionamento(i-1) = cond(H);
end
semilogy(2:i,condizionamento);
title("condizionamento matrice di Hilbert")
