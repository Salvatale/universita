close all
clear
clc

f = @(x) x.*exp(-x).*cos(2*x);
a = 0;
b = 2*pi;
times = 10;
val_esatto = -0.122122;

for j=1:times
    m = 10^j;
    x = linspace(a,b,m+1);
    H = (b-a)/m;
    ris_trap = H/2*(f(x(1))+f(x(end))+2*sum(f(x(1:m))));
    err(j) = abs(val_esatto-ris_trap);
end

loglog(10.^[1:j],err);
ris_trap
