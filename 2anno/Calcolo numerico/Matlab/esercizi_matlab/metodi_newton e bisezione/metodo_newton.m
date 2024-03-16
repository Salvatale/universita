function[num_iter,x] = metodo_newton(f,df,tolleranza,x0,max_iter)
x = x0;
num_iter = 0;
crit_arresto = abs(f(x));

while num_iter < max_iter && crit_arresto > tolleranza
    x_next = x - f(x)/df(x);
    crit_arresto = abs(f(x_next));
    x = abs(x_next);
    num_iter = num_iter + 1;
end
end