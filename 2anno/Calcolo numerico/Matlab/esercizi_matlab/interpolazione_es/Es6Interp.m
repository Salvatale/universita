clear
clc
close all
%approssimazione sqrt con 3 nodi
x=[0.49 0.64 0.81];
y=[0.7 0.8 0.9];
coeff=polyfit(x,y,2);
polyval(coeff,0.6);
sqrt(0.6);
err=abs(polyval(coeff,0.6)-sqrt(0.6))

%approssimazione sqrt con 4 nodi
x=[0.49 0.64 0.81 0.36];
y=[0.7 0.8 0.9 0.6];
coeff=polyfit(x,y,3);
polyval(coeff,0.6);
sqrt(0.6);
err=abs(polyval(coeff,0.6)-sqrt(0.6))