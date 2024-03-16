close all
clear all
clc

n = 1:100;

ris1 = (1+1./n).^n;
diff = abs(exp(1)-ris1(end))

ris2 = 4.*n./(n+2);
diff = abs(4-ris2(end))

ris3 = log(1+sqrt(n./(n+1)))
diff = abs(log(2)-ris3(end))

%esercizio 4

x=1:100;

ris4 = x.*(sqrt(x.^2+1)-x)
ris5 = x.*sqrt(x.^2+1)-x.^2
ris6 = x./(sqrt(x.^2+1)+x)
