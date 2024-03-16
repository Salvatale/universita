%esercizio 1
S(1)=0;

for i=1:10000
    S(i+1) = S(i)+0.0001;
end
S(end);
S(end) == 1.000;
err = abs(1-S(end))

pause
clear all
close all
clc
%esercizio 2

x = 77777777
y = sqrt(x^2+1)-x;
z = 1/(sqrt(x^2+1)+x);
err = abs(y-z)

pause
clear all
close all
clc

%esercizio 3
f1 = @(x) (1-x).^6;
f2 = @(x) x.^6-6*x.^5+15*x.^4-20*x.^3+15*x.^2-6*x+1;
i=0;
for delta = [0.1 0.01 0.005 0.0025]
    x = linspace(1-delta,1+delta);
    y1 = f1(x);
    y2 = f2(x);
    i =i+1;
    err = abs(y1-y2);
    subplot(2,2,i);
    %plot(x,y1);
    semilogy(x,y1);
    hold on
    %plot(x,y2);
    semilogy(x,y2)
    legend("y1","y2");
    title(delta);
end







