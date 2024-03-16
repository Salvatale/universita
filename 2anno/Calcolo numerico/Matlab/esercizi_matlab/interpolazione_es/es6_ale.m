close all
clear all
clc

format long e

n=2;
x = [0.49 0.64 0.81];
y = [0.7 0.8 0.9];
coeff = polyfit(x,y,n);
rad = polyval(coeff,0.6);
radice_06 = sqrt(0.6);
err = abs(radice_06-rad);