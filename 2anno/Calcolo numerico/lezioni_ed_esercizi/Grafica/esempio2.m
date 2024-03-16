close all
clear
clc

x = linspace(-2,2);
for k=1:4
    y = exp(-x.^2).*cos(k*pi*x);
    subplot(2,2,k);
    plot(x,y);
    title("k= "+k);
end