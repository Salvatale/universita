function [x,k] = Jacobi_matrix(A,b,tolleranza,max_iter)
    D = diag(diag(A));
    C = A-D;
    D_inv= inv(D);
    B = -D_inv*C;
    q = D_inv*b;
    x = ones(3,1);
    
    k = 0;
    while k < max_iter && norm(b-A*x) > tolleranza
        x = B*x+q;
        k = k+1;
    end
end