close all
clear
clc

a = -3;
b = 3;
f = @(x) abs(x-1);
k = 0;
for n = [5 10 20 40]
    nodi = linspace(a,b,n);
    y = f(nodi)';
    van = vander(nodi);
    coeff = van\y;
    x = linspace(a,b);
    funzione = f(x);
    fp = polyval(coeff,x);
    k = k+1;
    subplot(2,2,k);
    title("k = "+k);
    plot(nodi,y,'*');
    hold on
    plot(x,funzione);
    plot(x,fp);
    legend("nodi","funzione","polinomio interpolazione");
    err(k) = norm(funzione-fp,"inf");
end

figure
semilogy(1:k,err);
title("grafico errore");