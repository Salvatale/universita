close all
clear
clc
format short
n = 5;
A = diag(rand(n,1)) + diag(rand(n-1,1),1) + diag(rand(n-1,1),-1);
d0 = 1;

%passo 1
d(1) = A(1,1);
c = diag(A,1);
b = diag(A,-1);
a = diag(A);
d(2) = d(1)*a(2)-b(2)*c(1)*d0;

for k=3:n
    d(k) = d(k-1)*a(k)-b(k-1)*c(k-1)*d(k-2);
end

%costruzione matrice U
U = diag(c,1);
U(1,1) = d0/d(1);
for k=2:n
    U(k,k) = d(k)/d(k-1);
end
[L1,U1,P]=lu(A);
U
U1


%Ax=b -> LUx=t  Ux=y  Ly=t
%sostituzione in avanti
x_esatto = rand(n,1);
t = A*x_esatto;
y(1) = t(1);
y(2) = t(2) - b(1)*d0/d(1)*y(1);
for k=3:n
    y(k) = t(k) - b(k-1)*d(k-2)/d(k-1)*y(k-1);
end
y = y';
y_esatto = U*x_esatto;
err = abs(y_esatto-y);
y_esatto;
y;
x = inv(U)*y_esatto;
x_esatto;
err = abs(x_esatto-x);

% Ux=y
x1(n) = y(n)*d(n-1)/d(n);
for k=n-1:-1:2
    x1(k) = (y(k)-c(k)*x1(k+1))*d(k-1)/d(k);
end
x_esatto;
x1(1) = (y(1)-c(1)*x(2))*d0/d(1);
x1=x1';
err = abs(x_esatto-x1);





