close all
clear
clc

%radici con il comando roots
coeff = [1 -6 11 -6];
radici = roots(coeff)

coeff = [1 -7 15 -13 4];
radici = roots(coeff)

%radici con fzero

f1 = @(x) x.^3-6*x.^2+11*x-6;
x = 1.5;
fzero(f1,x)
fzero(f1,1.6)
fzero(f1,2.6)

f2 = @(x) x.^4-7*x.^3+15*x.^2-13*x+4;


%grafici funzioni
x = linspace(-2,5);
subplot(1,2,1);
plot(x,f1(x));
title("funzione 1");
subplot(1,2,2);
plot(x,f2(x));
title("funzione 2");

