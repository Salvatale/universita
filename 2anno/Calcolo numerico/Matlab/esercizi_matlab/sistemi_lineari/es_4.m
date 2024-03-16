close all
clc
clear
A = [2,3,1;1,-1,1;0,2,2];
B = [1,2,1;-1,2,-1;2,0,2];
C = [1,0,1;0,1,1;1,0,2];

%esercizio a
disp('esercizio a');
(A*B) == (B*A)
%oppure
abs(norm((A*B)-(B*A)))


%esercizio b
disp('esercizio b');
abs(norm(((A+B)+C)-(A+(B+C))))
(A+(B+C)) == ((A+B)+C)

%esercizio c 
disp('esercizio c');
abs(norm(A*(B*C)-((A*B)*C)))

%esercizio d
disp('esercizio d');
abs(norm((A*B)'-(B'*A')))



