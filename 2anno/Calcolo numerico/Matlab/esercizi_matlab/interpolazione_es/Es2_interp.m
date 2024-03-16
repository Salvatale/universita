close all
clear all
clc
%%%%Interpolazione
%Es.1
n=10;% Grado del polinomio
a=-5;
b=5;
x=linspace(a,b,n+1);%Nodi equispaziati
x_cheb=(a+b)/2-(b-a)/2*cos((2*[0:n]+1)/(2*n+2)*pi); %Nodi Chebyshev
f=@(x) 1./(1+x.^2); %Funzione di Runge
y=f(x); %valori nei nodi
y_cheb=f(x_cheb); %valori nei nodi Chebyshev
p=polyfit(x,y,n); %coefficienti polinomio interpolatore
p_cheb=polyfit(x_cheb,y_cheb,n); %coefficienti polinomio interpolatore Chebyshev
plot(x,y,'*')
hold on
plot(x_cheb,y_cheb,'*')
g=linspace(a,b);
h=polyval(p,g);
h_cheb=polyval(p_cheb,g);
plot(g,h)
plot(g,h_cheb)
y=f(g);
plot(g,y)
legend('punti equispaziati','punti Chebyshev','polinomio nodi equispaziati','polinomio nodi Chebyshev','funzione')
grid on