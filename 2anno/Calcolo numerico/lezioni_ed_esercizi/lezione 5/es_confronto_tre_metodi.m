close all
clear all
clc

a = 0;
b = 1.5;
tolleranza = 10^-10;
f = @(x) cos(2*x)^2-x^2;
errore = 1;
iter = 1;

%metodo bisezione

while errore > tolleranza
    x = (a+b)/2;
    if(f(x)*f(a)) < 0
        b = x;
    elseif (f(x)*f(a)) == 0
        return;
    else
        a = x;
    end
    errore = abs(b-a);
    e(iter) = errore;
    iter = iter+1;
end
iter
x
subplot(1,3,1);
semilogy([1:iter-1],e);
title("errore metodo di bisezione")

%metodo di Newton

num_iter = 0;
x = 1;
criterio_di_arresto = abs(f(x));
df = @(x) -4*cos(2*x)*(sin(2*x))-2*x;

%utilizzo criterio del residuo
while criterio_di_arresto > tolleranza
    x = abs(x - f(x)/df(x));
    criterio_di_arresto = abs(f(x));
    num_iter = num_iter+1;
    e_newton(num_iter) = criterio_di_arresto;
end
x
num_iter
subplot(1,3,2);
semilogy(1:num_iter,e_newton);
title("errore metodo newton con criterio del residuo");

if(num_iter < iter)
    disp('metodo newton fa meno iterazioni');
else
    disp('metodo bisezione fa meno iterazioni');
end

%utilizzo criterio dell'incremento

num_iter = 0;
criterio_di_arresto = 1;
while criterio_di_arresto > tolleranza
    x_next = abs(x - f(x)/df(x));
    criterio_di_arresto = abs(x_next-x);
    num_iter = num_iter+1;
    x = x_next;
    e_newton_incr(num_iter) = criterio_di_arresto;
end
x
num_iter
subplot(1,3,3);
semilogy(1:num_iter,e_newton_incr);
title("errore metodo newton criterio incremento");

