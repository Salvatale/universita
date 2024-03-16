close all
clear all
clc

x = [-3 5 8 0 1 5 -2 4];
x(6) = 100
x(1:3) = 5:7
x(4) =[]
x(4:7) = []
x = [1:3 x]
x = [x 10:12]

%parte b
A = eye(4)
A(1,1) = A(3,4)
A = [ones(4,1) A]
A = [A ones(4,1)]
A = [ones(1,6)*4;A]
A = [A;ones(1,6)*4]
A(3,:) = []
A(:,3) = []
