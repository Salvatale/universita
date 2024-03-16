close all
clear
clc

f = @(x) exp(x).*sin(2*x);
n = 5;
a = 0;
b = 2;
nodi = linspace(a,b,n+1);
nodi_polinomio = f(nodi);
%funzione
x = linspace(a,b);
funzione = f(x);

%polinomio interpolante
p = polyfit(nodi,nodi_polinomio,n);

%plot
plot(x,funzione);
hold on
plot(x,polyval(p,x));
plot(nodi,nodi_polinomio,'*');
title("grafico del polinomio");
legend("funzione","polinomio interpolazione","punti interpolazione");
