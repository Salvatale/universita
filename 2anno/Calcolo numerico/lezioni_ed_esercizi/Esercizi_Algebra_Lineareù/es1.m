close all
clear
clc

n = 3;
c = rand(n-1,1);
a = rand(n,1);
A = diag(a) + diag(c,1) + diag(c,-1)
tolleranza = 10^-5;
determinante = det(A);
if not(determinante == 0)
    d(1) = 1;
    d(2) = a(1);
    for i=3:n+1
       d(i) = d(i-1)*a(i-1)-c(i-2)^2*d(i-2);
    end
    
    diaginfL(1) = c(1)*d(1)/d(2);
    diaginfL(2) = c(2)*d(2)/d(3);
    L = diag(ones(n,1)) + diag(diaginfL,-1);
    for i=1:n
        diagU(i) = d(i+1)/d(i);
    end
    diagU;
    U = diag(diagU) + diag(c,1);
    A_fat = L*U
    err = abs(A-A_fat)
    norma = norm(A-A_fat)
    
else
    disp('matrice singolare');
end
