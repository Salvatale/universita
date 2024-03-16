close all
clear
clc

%fattorizzazione LU
n = 4;
A = rand(n)*10
x_esatto = rand(n,1)*10;
b = A*x_esatto;

L = diag(ones(n,1));
U = zeros(n);

%passo 1
U(1,:) = A(1,:);
L(2:n,1) = A(2:n,1)/U(1,1);
%passo 2
for k=2:n
    U(k,k:n) = A(k,k:n) - L(k,1:k-1)*U(1:k-1,k:n);
    L(k+1:n,k) = (A(k+1:n,k)-L(k+1:n,1:k-1)*U(1:k-1,k))/U(k,k);
end
L
U
A_fatt = L*U
[L1,U1] = lu(A)
norma = norm(A-A_fatt)
errore = abs(A-A_fatt)




