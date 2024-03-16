clear
clc
close all

n = 4;
A = rand(n);
det(A)
in = inv(A);

for i=1:n
    I(:,i) = A*in(:,i);
end
err = norm(eye(n)-I)


