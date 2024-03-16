x = [0:0.01:1];
f1 = ((1-x./24)./(1+x./24 + x.^2./384)).^8
plot(x, f1)
title('Prima Funzione')
figure
x1 = linspace(-pi,0,101);
x2 = linspace(0,pi,101);
f2 = exp(-x1.^2);
f3 = cos(x2);
%A =  [f2;f3];
%plot(x1, f2, x2, f3)
A = [f2 f3];
X = [x1 x2];
plot(X,A)
%altra possibilità
plot(x1,f2)
hold on
plot(x2,f3)