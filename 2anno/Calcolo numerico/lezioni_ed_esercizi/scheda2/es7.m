close all
clear all
clc
A = ((1:8).*ones(8))'
S = triu(A)
I = tril(A)
S = S - diag(1:8)
I = I -diag(0:7)

%parte b

B1 = diag(diag(A)) + diag(diag(A,1),1) + diag(diag(A,-1),-1)
B2 = diag(diag(A)) + diag(diag(A,1),1)
B3 = diag(diag(A)) + diag(diag(A,-1),-1)