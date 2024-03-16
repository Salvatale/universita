close all
clear
clc

n = 3;

A = [1 1/2 1/3;1/2 1/3 1/4;1/3 1/4 1/5];
b = [11/6 13/12 47/60]';
for i=2:n
    for j=i:n
        m = -A(j,i-1)/A(i-1,i-1);
        A(j,:) = m*A(i-1,:)+A(j,:);
        b(j) = m*b(i-1)+b(j);
    end
end
A
b

A_gauss_esatta = [1 1/2 1/3;0 1/12 1/12;0 0 1/180];
errore = abs(A_gauss_esatta-A)
norma = norm(A_gauss_esatta-A)
x_esatto = A_gauss_esatta\b;
x(n) = b(n)/A(n,n);


for i=n-1:-1:1
    x(i) = (b(i)-A(i,i+1:n)*(x(i+1:n))')/A(i,i);
end

errore = abs(x_esatto-x)
x_esatto
x

