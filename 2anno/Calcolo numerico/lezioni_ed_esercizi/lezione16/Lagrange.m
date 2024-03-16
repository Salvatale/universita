close all
clear
clc

x = [3 7 11];
y = [9 49 121];
L0 = @(x) (x.^2-18*x+77)./32;
L1 = @(x) (x.^2-14*x+33)./-16;
L2 = @(x) (x.^2-10*x+21)./32;

x = 1:100;
p = y(1)*L0(x)+y(2)*L1(x)+y(3)*L2(x);

% p = x^2 , plottiamo cosi verifichiamo

p_esatto = x.^2;
err = norm(p_esatto-p)
plot(x,p);
title("grafico del polinomio di Lagrange");
