close all
clear all
clc

%f = @(x) exp(x).*cos(4*x);
f =@(x) abs(x-1);
a = -3;
b = 3;
n = 40;

    x1 = linspace(a,b,n+1);
    x2 = linspace(a,b);
    
    y = f(x1);

    Matrice_Vandermonde = vander(x1);
    coeff = Matrice_Vandermonde\y';

    y_interp = polyval(coeff,x2);
    y_fun = f(x2);
    err = norm(y_interp-y_fun,"inf");

err
plot(x2,y_interp);
hold on
plot(x2,y_fun);
plot(x1,y,'*');
legend("polinomio interpolazione","funzione","nodi interpolazione");
grid on

%figure
%plot(err);
%title("figura errore");
