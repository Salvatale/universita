close all
clear
clc

n = 21;
x = linspace(0,2*pi,n);
y = cos(x);
plot(x,y,'-o');
title("grafico coseno")