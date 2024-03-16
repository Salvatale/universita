close all
clear all
clc

p1 = @(x) 1+x;
p2 = @(x) 1+x+x^2/2;
x = 0.1;

ea1 = abs(exp(x)-p1(x))
ea2 = abs(exp(x)-p2(x))
er1 = abs(exp(x)-p1(x))/exp(x)
er2 = abs(exp(x)-p2(x))/exp(x)

pause

%calcolare le radici di queste equazioni

close all
clear all
clc

f = @(t) 2*t^2-4*t-1;
coeff = [2 -4 -1];
radici = roots(coeff)

f = @(x) x^4+2*x^2-3;
coeff = [1 0 2 0 -3];
radici2 = roots(coeff)
