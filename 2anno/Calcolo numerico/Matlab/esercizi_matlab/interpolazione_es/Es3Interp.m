clear
clc
close all

a=-3;
b=3;
k=0;
for n=[5,10,20,40]
    k=k+1;
    %n=5; %numero di nodi
    
    f = @(x) exp(x).*cos(4*x); %@(x) abs(x-1); %
    
    g = linspace(a,b,n); %nodi di interpolazione
    g1 = linspace(a,b); %griglia per la valutazione dell'errore
    ys = f(g);
    
    van = vander(g); %matrice di Vandermonde
    coeff = van\ys'; %coefficienti polinomio interpolazione
    
    y_interp = polyval(coeff, g1);
    y_corr = f(g1);
    
    err(k) = norm(y_interp - y_corr, "inf"); %errore
    %disp(err)
end

plot(g1, polyval(coeff, g1));
hold on;
plot(g1, f(g1));
hold on;
plot(g, ys, "*");
legend('polinomio interp','funzione','punti interpolazione')
grid on

figure
plot([1:k],err)
title('grafico errore')
xlabel('numero di nodi')
grid on