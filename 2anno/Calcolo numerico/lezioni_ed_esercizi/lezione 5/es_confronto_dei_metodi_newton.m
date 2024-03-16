close all
clear all
clc

x_incr = 18;
x_res = 20;
tolleranza = 10^-3;
f = @(x) exp(-x)*-10^-9;
df = @(x) exp(-x)*10^-9;
criterio_incremento = 1;
criterio_residuo = 1;
iter_incr = 0;
iter_res = 0;

%ciclo criterio incremento
while criterio_incremento > tolleranza
    x_next = abs(x_incr - f(x_incr)/df(x_incr));
    criterio_incremento = abs(x_next-x_incr);
    x_incr = x_next;
    iter_incr = iter_incr+1;
    e_incr(iter_incr) = criterio_incremento;
end

%ciclo criterio residuo
while criterio_residuo > tolleranza
    x_res = abs(x_res - f(x_res)/df(x_res));
    criterio_residuo = abs(f(x_res));
    iter_res = iter_res+1;
    e_residuo(iter_res) = criterio_residuo;
end
subplot(1,2,1);
semilogy(0:iter_incr,criterio_incremento);
title("errore con criterio dell'incremento")
iter_incr
x_incr
subplot(1,2,2);
semilogy(0:iter_res,e_residuo);
title("errore criterio residuo");
iter_res
x_res



