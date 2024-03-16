close all
clear
clc

n = 40;
A = triu(rand(n));
x_esatto = rand(n,1);
b = A*x_esatto;

%passo 1
x(n) = b(n)/A(n,n);

for i=n-1:-1:1
    x(i) = (b(i)-A(i,i+1:n)*(x(i+1:n))')/A(i,i);
end
x = x'
x_esatto
err = abs(x_esatto-x)