close all
clear
clc
n=4;

v1 = rand(n,1);
v2 = rand(n-1,1);

A = diag(v1) + diag(v2,1) + diag(v2,-1);

