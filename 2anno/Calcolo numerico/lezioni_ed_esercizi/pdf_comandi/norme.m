close all
clear
clc
format long e

x = [1 -2]

p = 1;
norma_esatta = norm(x,p)
norma = (sum(abs(x.^p)))^(1/p)
err1 = abs(3-norma)
err2 = abs(3-norma_esatta)

p = 2;
norma_esatta = norm(x,p)
norma = (sum(abs(x.^p)))^(1/p)
err1 = abs(sqrt(5)-norma)
err2 = abs(sqrt(5)-norma_esatta)

p = inf;
norma_esatta = norm(x,p)
norma = max(abs(x))
err = abs(2-norma_esatta)

