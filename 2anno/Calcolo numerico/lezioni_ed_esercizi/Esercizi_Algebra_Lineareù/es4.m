close all
clear
clc

A = [2 3 1;1 -1 1;0 2 2];
B = [1 2 1;-1 2 -1;2 0 2];
C = [1 0 1;0 1 1;1 0 2];

disp('esercizio a');
norm(A*B-B*A)
disp('esercizio b');
norm(((A+B)+C)-(A+(B+C)))
disp('esercizio c');
norm((A*(B*C))-((A*B)*C))
disp('esercizio d')
norm((A*B)'-(B'*A'))