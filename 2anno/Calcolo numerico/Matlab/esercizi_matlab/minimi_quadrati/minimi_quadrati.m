close all
clear all
clc
%format long e
sigma = [0.00 0.06 0.14 0.25 0.31 0.47 0.60 0.70];
epsilon = [0.00 0.08 0.14 0.20 0.23 0.25 0.28 0.29];

%coeffificienti retta con polyfit
% y=mx+q grado 1
coeff = polyfit(sigma,epsilon,1);

%coefficienti con con la retta dei minimi quadrati

q = (sum(epsilon).*sum(sigma.^2)-sum(sigma).*sum(sigma.*epsilon))...
    ./(length(sigma).*sum(sigma.^2)-(sum(sigma).^2));

m = (length(sigma).*sum(sigma.*epsilon)-sum(sigma).*sum(epsilon))...
    ./(length(sigma).*sum(sigma.^2)-(sum(sigma).^2));

coeff2 = [m q];
err_coeff = abs(coeff-coeff2)

retta1 = polyval(coeff,0.9);
retta2 = polyval(coeff2,0.9);
err_retta = abs(retta1-retta2);
plot(sigma,epsilon,'*');
hold on
x = linspace(0,0.9);
plot(x,polyval(coeff,x));

%interpolazione semplice
coeff_interpolanti = polyfit(sigma,epsilon,length(sigma)-1);
plot(x,polyval(coeff_interpolanti,x));

%parabola dei minimi quadrati
coeff_parabola = polyfit(sigma,epsilon,2);
plot(x,polyval(coeff_parabola,x));

legend("punti","retta minimi quadrati","interpolazione semplice","parabola minimi quadrati");
xlabel("sforzi")
ylabel("deformazioni")

%residuo retta dei minimi quadrati
for i=1:length(sigma)
    r(i) = epsilon(i)-m*sigma(i)-q;
end
r
