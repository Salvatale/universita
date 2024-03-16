close all
clear
clc

n = 22;
a = -1;
b = 1;
f = @(x) sin(x);
nodi = linspace(a,b,n);
y1 = f(nodi);
y2 = sin(nodi).*(1+(-1).^[1:n]*10^-4);
p = polyfit(nodi,y1,n-1);
p_pert = polyfit(nodi,y2,n-1);
x = linspace(a,b);
err = norm(p-p_pert)
fun = f(x);
plot(x,fun);
hold on
plot(nodi,y1,'*');
plot(x,polyval(p,x));
plot(nodi,y2,'*');
plot(x,polyval(p_pert,x));
legend("funzione","nodi","polinomio interpolante", ...
    "nodi perturbati","polinomio perturbato");
