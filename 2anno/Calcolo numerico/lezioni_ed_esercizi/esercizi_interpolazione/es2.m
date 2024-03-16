close all
clear
clc

n = 10;
Runge = @(x) 1./(1+x.^2);
a = -5;
b = 5;
nodi_equispaziati = linspace(a,b,n+1);
x = linspace(a,b);
funzione = Runge(x);
funzione_nodi = Runge(nodi_equispaziati);
p = polyfit(nodi_equispaziati,funzione_nodi,n);

%Chebyshev
nodi_chebyshev = (a+b)/2-(b-a)/2*cos((2*[0:n]+1)/(2*n+2)*pi);
funzione_nodi_Chebyshev = Runge(nodi_chebyshev);
p_chebyshev = polyfit(nodi_chebyshev,funzione_nodi_Chebyshev,n);


%plot

plot(x,funzione);
hold on
plot(nodi_equispaziati,funzione_nodi,'*');
plot(x,polyval(p,x));
plot(nodi_chebyshev,funzione_nodi_Chebyshev,'*');
plot(x,polyval(p_chebyshev,x));
legend("funzione","nodi","polinomio interpolazione", ...
    "nodi Chebyshev","polinomio Chebyshev");