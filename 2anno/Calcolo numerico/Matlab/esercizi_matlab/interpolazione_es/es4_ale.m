close all
clear all
clc

nodi = 22;
a=-1;
b=1;
f = @(x) sin(x);
x = linspace(a,b,nodi);
y = f(x);
coeff = polyfit(x,y,nodi-1);

yperturbato = f(x).*(1+(-1).^[1:nodi].*10^-4);
err_dati = norm(y-yperturbato);
coeff_perturbati = polyfit(x,yperturbato,nodi-1);

x2 = linspace(a,b);

plot(x,y,'*');
hold on
plot(x,yperturbato,'*');
plot(x2,polyval(coeff,x2));
plot(x2,polyval(coeff_perturbati,x2));
plot(x2,f(x2));
legend("nodi interpolazione","nodi polinomio perturbato","polinomio di interpolazione","polinomio perturbato","funzione");

err = norm(polyval(coeff,x2) - f(x2))
err_perturbato = norm(polyval(coeff_perturbati,x2)-f(x2))
