close all
clear
clc

x = 0:8;
y_esatto = [2 2.4 2.75 3.1 3.5 3.9 4.25 4.6 5];

q = 2;
m = 3/8;

f = @(x) m*x+q;
y = f(x);
r = y_esatto-y;

r
plot(x,y_esatto,'*');
hold on
plot(x,f(x));
plot(x,y,'*');

%minimizziamo il quadrato dei residui
qm = (sum(y_esatto)*sum(x.^2)-sum(x)*sum(x.*y_esatto))/...
    (length(x)*sum(x.^2)-sum(x)^2);
mm = (length(x)*sum(x.*y_esatto)-sum(x)*sum(y_esatto))/...
    (length(x)*sum(x.^2)-sum(x)^2);

err_q = abs(q-qm)
err_m = abs(m-mm);
f_min_quadr = @(x) mm*x+qm;
plot(x,f_min_quadr(x));

legend("nodi","retta","nodi calcolati","retta minimi quadrati");

