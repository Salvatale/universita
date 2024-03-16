for m=1:6
    x1 = linspace(-m,0,50);
    x2 = linspace(0,m,50);
    f1 = (m-x1.^2/m).^m;
    f2 = (x2.^2/m+m).^m;
    X = [x1 x2];
    F = [f1 f2];
    %plot(X,F)
    %semilogy(X,F)
    subplot(2,3,m)
    plot(X,F)
    title(m);
    grid on
    hold on
end