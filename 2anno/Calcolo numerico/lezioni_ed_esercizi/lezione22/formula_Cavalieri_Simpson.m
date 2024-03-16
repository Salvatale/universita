close all
clear
clc

f = @(x) x.*exp(-x).*cos(2*x);
a = 0;
b = 2*pi;
times = 5;
val_esatto = -0.122122;

for j=1:times
    m = 10^j;
    x = linspace(a,b,m+1);
    H = (b-a)/m;
    i =1:m;
    fx0 = f(x(1));
    sum_1 = 2*sum(f(x(i)));
    sum_2 = 4*sum(f((x(i)+x(i+1))/2));
    fxm = f(x(m));
    ris_CS = H/6*(fx0 + sum_1 + sum_2 + fxm);
    err(j) = abs(val_esatto-ris_CS);
end

loglog(10.^[1:j],err);
ris_CS