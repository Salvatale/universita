close all
clear
clc

n = 5;
A = rand(n);
x_esatto = rand(n,1);
t = A*x_esatto;

%calcolare d,b,c
b = diag(A,-1);
c = diag(A,1);

d0 = 1;
d(1) = A(1,1);
d(2) = d(1)*A(2,2)-b(1)*c(1)*d0;
for k=3:n
    d(k) = d(k-1)*A(k,k)-b(k-1)*c(k-1)*d(k-2);
end

%calcolare Ly = t, LUx = t, Ux = y
%sostituzione in avanti
y(1) = t(1);
y(2) = t(2) - b(1)*d0/d(1)*y(1); 
for k=3:n
    y(k) = t(k)-b(k-1)*d(k-2)*d(k-1)*y(k-1);
end
y = y'

%calcolare Ux=y
%sostituzione indietro
x(n) = y(n)*d(n-1)/d(n);
for k=n-1:-1:2
    x(k) = (y(k)-c(k)*x(k+1))*d(k-1)/d(k);
end
x(1) = (y(1)-c(1)*x(2))*d0/d(1);
x = x'
x_esatto
norma = norm(x_esatto-x)
err = abs(x_esatto-x)











