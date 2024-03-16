function[x] = matr_diag_sol(A,b)
    [n,m] = size(b);
    for i=1:n
        x(i,1)=b(i)/A(i,i);
    end
    
end