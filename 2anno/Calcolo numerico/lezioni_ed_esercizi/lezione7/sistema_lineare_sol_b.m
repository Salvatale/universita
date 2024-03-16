close all
clear
clc

%es1

n = 2;
A = [3 2;-1 2];
if not(det(A) == 0) 
    b = [18;2];
    x = A\b
else
    disp('matrice singolare');
end


%es2
n = 2;
A = [-1/2 1;-1/2 1];
if not(det(A) == 0) 
    b = [1;1/2];
    x = A\b
else
    disp('matrice singolare');
end

%es3
n = 2;
A = [-1/2 1;-1 2];
if not(det(A) == 0) 
    b = [1;2];
    x = A\b
else
    disp('matrice singolare');
end

%es4
n = 2;
A = [-2.3/5 1;-1/2 1];
if not(det(A) == 0) 
    b = [1.1;1];
    x = A\b
else
    disp('matrice singolare');
end

