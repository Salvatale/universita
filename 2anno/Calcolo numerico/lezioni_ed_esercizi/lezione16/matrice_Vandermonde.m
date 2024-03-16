close all
clear
clc

grado = 2;
x = [300 400 500]';
Vandermonde1 = [x.^2 x ones(3,1)]
Vandermonde2 = vander(x)
err = norm(Vandermonde2-Vandermonde1)
y_esatto = [0.616;0.525;0.457];

a = Vandermonde1\y_esatto;

%calcolo di y_k => p(x_k) = y_k

for i=1:grado+1
    y(i,1) = Vandermonde1(i,:)*a;
end
err = norm(y_esatto-y)
y
y_esatto
