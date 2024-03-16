clear
clc
format long

n=100;

%Metodo avanti
%A=tril(rand(n));
%d=ones(n-1,1)*2;
d=ones(n-1,1);
A=eye(n)+diag(d,-1);

b=rand(n,1);
x=metodo_in_avanti(A,b);
x=x';

%Controllo
norma=norm(A*x-b)
condizionamento=cond(A)

%Medodo indietro
A=A';
xesatto=ones(n,1);
b=A*xesatto;
x=metodo_indietro(A,b);
x=x';
%residuo=norm(A*x-b);
errore=norm(x-xesatto)
condizionamento=cond(A);




