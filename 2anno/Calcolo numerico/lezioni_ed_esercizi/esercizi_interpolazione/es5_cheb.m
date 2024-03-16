close all
clear
clc

a = -1;
b = 1;
f = @(x) exp(x) +1;
n = 10;

x_cheb = cos((2*[0:n]+1)*pi/(2*n+2));
van = vander(x_cheb);
y = f(x_cheb);
coeff = van\y';
x = linspace(a,b);
funzione = f(x);

%dati perturbati
e = @(i) -1.^i.*10-5;
f_pert = @(x) f(x)+e(x);
y_pert = f_pert(x_cheb);
coeff_pert = van\y_pert';

%plot
plot(x_cheb,y,'*');
hold on
plot(x,polyval(coeff,x));
plot(x,f(x));
plot(x_cheb,y_pert,'*');
plot(x,polyval(coeff_pert,x));
plot(x,f_pert(x));
legend("nodi","polinomio interpolazione","funzione" ,...
    "nodi perturbati","polinomio perturbato","funzione perturbata");
max = max(coeff-coeff_pert)
t = linspace(a,b,101);
max_p = max(abs(polyval(coeff,t)-polyval(coeff_pert,t)))








