% x_i = 300,400,500
% y_i = 0.616 0.525 0.457
% cond(V) = 5.893+10^-6


x = [300 400 500]';
y = [0.616 0.525 0.457]';

V = [ones(3,1) x x.^2];
condizionamento = cond(V);

a = inv(V)*y
V*a
y