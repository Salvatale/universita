clear
clc
close all

sigma = [0.00 0.06 0.14 0.25 0.31 0.47 0.60 0.70];
epsilon = [0.00 0.08 0.14 0.20 0.23 0.25 0.28 0.29];
%retta minimi quadrati
coeff = polyfit(sigma,epsilon,1);
%formule coefficienti retta minimi quadrati
q = (sum(epsilon).*sum(sigma.^2)-sum(sigma)*(sum(sigma.*epsilon)))./...
(length(sigma)*sum(sigma.^2)-(sum(sigma)^2));

m = (length(sigma)*(sum(sigma.*epsilon))-sum(sigma)*sum(epsilon))./...
    (length(sigma)*sum(sigma.^2)-(sum(sigma)^2));


retta = polyval(coeff,0.9);

plot(sigma,epsilon,'*');
hold on;
x = linspace(0.00,0.9);
plot(x,polyval(coeff,x));
%interpolazione semplice
coeff2 = polyfit(sigma,epsilon,length(sigma)-1); 
%plot(x,polyval(coeff2,x));
%parabola minimi quadrati
coeff3 = polyfit(sigma,epsilon,2);
plot(x,polyval(coeff3,x));

legend('dati','retta minimi quadrati','parabola minimi quadrati')
grid on
xlabel('stress')
ylabel('deformazioni')


