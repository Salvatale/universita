close all
clear
clc

a = -1;
b = 1;
f = @(x) exp(x) +1;
n = 10;
x = linspace(a,b,n+1);
van = vander(x);
y = f(x);
a_coe = van\y';
x1 = linspace(a,b);
plot(x,y,'*');
hold on
plot(x1,polyval(a_coe,x1));
plot(x1,f(x1));



e = @(i) -1.^i*10^-5;
f_pert = @(x) f(x)+e(x);
y_pert = f_pert(x);
p_pert = van\y_pert';
plot(x,y_pert,'*');
plot(x1,polyval(p_pert,x1));
plot(x1,f_pert(x1));

legend("nodi","funzione","polinomio interpolante","nodi pert", ...
    "polinomio perturbato","funzione perturbata");
err = norm(a_coe-p_pert)
max = max(a_coe-p_pert)
t = linspace(-1,1,101);
f_t = f(t);
f_pert_t = f_pert(t);
max_p = max(f_pert_t-f_t)


