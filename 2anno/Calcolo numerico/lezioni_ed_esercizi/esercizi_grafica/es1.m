close all
clear
clc

%esercizio a
x_es_1 = linspace(0,1,101);
y_es_1 = ((1-x_es_1./24)./(1+x_es_1./24+x_es_1.^2./384)).^8;
subplot(2,2,1);
title("esercizio 1");
plot(x_es_1,y_es_1);
title("funzione 1");

%esercizio b
x1_es2 = linspace(-2,0,101);
y1_es2 = (2-x1_es2.^2./2).^2;
x2_es2 = linspace(0,2,101);
y2_es2 = (x2_es2.^2./2+2).^2;
subplot(2,2,2);
x_es2 = [x1_es2 x2_es2];
y_es_2 = [y1_es2 y2_es2];
plot(x_es2,y_es_2);
title("funzione 2")

%esercizio c
x1_es3 = linspace(-pi,0,101);
x2_es3 = linspace(0,pi,101);
y1_es3 = exp(-x1_es3.^2);
y2_es3 = cos(x2_es3);
x_es3 = [x1_es3 x2_es3];
y_es3 = [y1_es3 y2_es3];
subplot(2,2,3);
plot(x_es3,y_es3);
title("funzione 3");





