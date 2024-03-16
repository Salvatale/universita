function [x] = metodo_in_avanti(A,b)
    [n,m] = size(b);
    x(1) = b(1) / A(1,1);
    for i=2:n
        x(i) = (b(i)-A(i,1:i-1)*(x(1:i-1))')/ A(i,i);
    end
end