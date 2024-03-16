close all
clear
clc

n = 3;
A = [-3 3 -6;-4 7 -8;5 7 -9];
x_esatto = rand(n,1);
b = A*x_esatto;
x = ones(n,1);
criterio_residuo = norm(A*x-b);
num_iter = 0;
max_iter = 1000;
tolleranza = 10^-5;

%metodo Jacobi
D = diag(diag(A));
C = A-D;
B_j = -inv(D)*C;
q_j = inv(D)*b;
while criterio_residuo > tolleranza && num_iter < max_iter
    x = B_j*x+q_j;
    criterio_residuo = norm(A*x-b);
    num_iter = num_iter+1;
end
err = norm(x_esatto-x)
x
x_esatto
num_iter
%converge


%metodo Gauss-Seidel
num_iter = 0;
x = ones(n,1);
criterio_residuo = norm(A*x-b);
D = diag(diag(A));
E = tril(A);
F = triu(A);
B_gs = -inv(E+D)*F;
q_gs = inv(E+D)*b;

while criterio_residuo > tolleranza && num_iter < max_iter
    x = B_gs*x+q_gs;
    num_iter = num_iter+1;
end

num_iter
err = norm(x_esatto-x)
x_esatto
x