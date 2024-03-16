close all
clear all
clc

format long e

for a=1:10
    p = 10^a;
    b = (1+p^2)/p;

    coeff = [1 0 -b 0 1];
    radici = (roots(coeff))';
    x1 = 1/sqrt(p);
    x2 = -1/sqrt(p);
    x3 = sqrt(p);
    x4 = -sqrt(p);
    x = [x4,x3,x2,x1];
    err(a) = norm(radici-x);
end

err
semilogy(err)
title("grafico dell'errore relativo");