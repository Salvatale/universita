close all
clear
clc

grado = 15;
f = @(x) 1./(1+x.^2);
a = -5;
b = 5;
nodi = linspace(a,b,grado+1); %nodi del polinomio
y = f(nodi);
plot(nodi,y,'*');
hold on

%troviamo il polinomio interpolante
coeff = polyfit(nodi,y,grado);
x = linspace(a,b);
plot(x,polyval(coeff,x));

%troviamo la funzione
fun = f(x);
plot(x,fun);

legend("nodi interpolazione","polinomio interpolante","funzione");