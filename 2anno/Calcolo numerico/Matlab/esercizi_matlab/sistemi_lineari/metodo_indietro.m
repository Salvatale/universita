function x = metodo_indietro(A,b)
    [n,m] = size(b);

    %passo 1
    x(n) = b(n)/A(n,n);

    %passo 2
    for i=n-1:-1:1
        x(i) = (b(i)-A(i,i+1:n)*(x(i+1:n))')/A(i,i);
    end
end