close all
clear all
clc

n = 15;
a = -5;
b = 5;
f_Runge = @(x) 1./(1+x.^2);
x = linspace(a,b,n+1);
y_Runge = f_Runge(x);
coeff_Runge = polyfit(x,y_Runge,n);
plot(x,y_Runge,'*');

hold on

x1 = linspace(a,b);
g_Runge = polyval(coeff_Runge,x1);
plot(x1,g_Runge);

i = 0:n;
x_chebyshev = (a+b)/2-(b-a)/2.*cos((2*i+1)./(2*n+2).*pi);
y_chebyshev = f_Runge(x_chebyshev);
plot(x_chebyshev,y_chebyshev,'*');
coeff_chebyshev = polyfit(x_chebyshev,y_chebyshev,n);
g_chebyshev = polyval(coeff_chebyshev,x1);
plot(x1,g_chebyshev);

fun = f_Runge(x1);
plot(x1,fun);

legend("nodi equispaziati","polinomio nodi equispaziati","nodi Chebyshev","polinomio Chebyshev","funzione di Runge")

