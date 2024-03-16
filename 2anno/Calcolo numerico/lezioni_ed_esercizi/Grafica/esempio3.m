close all
clear
clc

x = linspace(0,2*pi);
y1 = sin(x);
y2 = cos(x);
plot(x,y1);
hold on
plot(x,y2);
legend("funzione coseno","funzione seno");
title("funzioni sovvrapposte");