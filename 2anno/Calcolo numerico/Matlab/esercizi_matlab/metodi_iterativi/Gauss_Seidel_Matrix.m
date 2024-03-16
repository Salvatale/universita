function [x,k] = Gauss_Seidel_Matrix(A,b,tolleranza,max_iter)
    D = diag(diag(A));
    E = tril(A,-1);
    F = triu(A,1);
    B = -inv(E+D)*F;
    q = inv(E+D)*b;
    [n,m] = size(b);
    x = ones(n,m);
    k = 0;
    while k < max_iter && norm(b-A*x) > tolleranza
        x = B*x+q;
        k = k+1;
    end
end