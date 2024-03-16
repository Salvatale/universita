for m=1:6
    x1 = linspace(-m,0,40);
    x2 = linspace(0,m,40);
    f1 = (m - x1.^2/m).^m;
    f2 = (x2.^2/m + m).^m;
    X = [x1 x2];
    F = [f1 f2];
    plot(X,F);
    hold on
    pause
end

pause

for m=1:6
    x1 = linspace(-m,0,40);
    x2 = linspace(0,m,40);
    f1 = (m - x1.^2/m).^m;
    f2 = (x2.^2/m + m).^m;
    X = [x1 x2];
    F = [f1 f2];
    subplot(2,3,m);
    plot(X,F);
end