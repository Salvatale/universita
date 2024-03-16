close all
clear all
clc

e = @(t) 7*exp(-5*t)+3*exp(-2*t)-5;

ris = 0;
for i=0:100
    if e(i) == 5
        ris = e(i);
        break; 
    end
end
disp("per avere e(x)=5 dobbiamo avere t= "+i)