close all
clear all
clc
%%%%Interpolazione
%Es.1
n=5; % Grado del polinomio
a=0; 
b=2; 
x=linspace(a,b,n+1);% Nodi 
f=@(x) exp(x).*sin(2*x); %funzione
y=f(x); %valori nei nodi
p=polyfit(x,y,n); %coefficienti polinomio interpolatore
plot(x,y,'*')
hold on
g=linspace(a,b);
h=polyval(p,g);
plot(g,h)
y=f(g);
plot(g,y)
legend('punti interpolazione','polinomio interpolante','funzione')
grid on