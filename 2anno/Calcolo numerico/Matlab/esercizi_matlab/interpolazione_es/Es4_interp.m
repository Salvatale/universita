close all
clear
clc

n=22;       % numero nodi
a=-1;
b=1;
x = linspace(a,b,n);  %nodi
y=sin(x); %valori nei nodi
m = polyfit(x,y,n-1);   %coefficienti polinomio interpolazione
y_bis=sin(x).*(1+(-1).^[1:n]*10^-4); %valori perturbati nei nodi
err_dati=norm(y-y_bis) %errore sui dati
mbis = polyfit(x,y_bis,n-1);
g = linspace(a,b,100);      %griglia equispaziata
plot(x,y,"*")            %plot punti interpolazione
hold on
plot(x,y_bis,"*")  %plot punti perturbati
plot(g,sin(g)) %plot funzione 
plot(g,polyval(m,g)) %plot polinomio
plot(g,polyval(mbis,g)) %plot polinomio perturbato
grid on
legend('punti interp','punti perturbati','funzione','polinomio','polinomio perturbato')
err = norm(polyval(m,g) - sin(g))
errbis= norm(polyval(mbis,g)-sin(g))
