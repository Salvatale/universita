close all
clear all
clc

a = -1;
b = 1;
n = 10;
x = linspace(a,b);
xi = linspace(a,b,n+1);
x_cheb = (a+b)/2-(b-a)/2*cos((2*[0:n]+1)/(2*n+2)*pi);

for i=1:length(x)
    Wn(i) = abs(prod(x(i)-xi));
    Wn_cheb(i) = abs(prod(x(i)-x_cheb));
end

plot(x,Wn);
hold on
plot(x,Wn_cheb);
legend("Wn","Wncheb")