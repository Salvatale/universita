close all
clear all
clc

n = 5;
a=0;
b=2;
f = @(x) exp(x).*sin(2*x);
x = linspace(a,b,n+1); %vettore con n+1 nodi
y = f(x); 
plot(x,y,'*'); %nodi del polinomio interpolante

hold on

%polinomio interpolante
x1 = linspace(a,b);
y1 = f(x1); %funzione su 100 punti
coeff_p = polyfit(x1,y1,n); %coefficienti polinomio di interpolazione
val_p = polyval(coeff_p,x1);
plot(x1,val_p); %grafico polinomio interpolatore
plot(x1,y1); %grafico funzione
grid on
legend("nodi polinomio interpolatore","polinomio interpolatore","f(x1)")

