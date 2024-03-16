close all
clear
clc

n = 10;
A = tril(rand(n));
x_esatto = rand(n,1);
b = A*x_esatto;

%passo 1
x(1) = b(1)/A(1,1);

for i=2:n
    x(i) = (b(i)-(A(i,1:i-1)*(x(1:i-1))'))/A(i,i);
end
x = x'
x_esatto
err = abs(x_esatto-x)