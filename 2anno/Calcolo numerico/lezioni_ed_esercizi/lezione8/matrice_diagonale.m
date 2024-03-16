close all
clear
clc

n = 4;
A = diag(rand(n,1)*10);
x_esatto = rand(n,1)*10;
b = A*x_esatto;

for i=1:n
    x(i,1) = b(i)/A(i,i);
end
x
x_esatto
err = abs(x_esatto-x)
plot(err)