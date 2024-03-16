close all
clear
clc

a = 0;
b = 2*pi;
f = @(x) x.*exp(-x).*cos(2*x);
x1 = linspace(a,b);
fun = f(x1);
ris_integrazione = (3*(exp(-2*pi)-1)-10*pi*exp(-2*pi))/25

times = 5;
for j=1:times
    m = 10^j;
    x = linspace(a,b,m+1);
    H = (b-a)/m;
    i =1:m;
    res(j) = H*sum(f((x(i)+x(i+1))/2));
    err(j) = abs(ris_integrazione-res(j));
    y = f(x);
    p = polyfit(x,y,m);
    %subplot(2,3,j);
    %plot(x,y,'*');
    hold on
    %plot(x1,polyval(p,x1));
    %plot(x1,fun);
    %title("t = "+j);
    %legend("nodi interpolazione","polinomio interpolazione","funzione");
end

figure
loglog(10.^(1:times),err);
res

