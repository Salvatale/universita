clear
clc
close all
a=-1;
b=1;
n=10;
x=linspace(a,b);
% for i=0:n
%     x_cheb(i+1)=(a+b)/2-(b-a)/2*cos((2*i+1)/(2*n+2)*pi);
% end
x_cheb=(a+b)/2-(b-a)/2*cos((2*[0:n]+1)/(2*n+2)*pi); % nodi di Chebyshev
xi=linspace(a,b,n+1); %nodi equispaziati
for i=1:length(x)
Wn(i)=abs(prod(x(i)-xi));
Wn1(i)=abs(prod(x(i)-x_cheb));
end
plot(x,Wn);
hold on
plot(x,Wn1);
