close all
clear
clc
%grafici sovvraposti
for m=1:6
    x1 = linspace(-m,0);
    x2 = linspace(0,m);
    y1 = (m-x1.^2./m).^m;
    y2 = (x2.^2./m+m).^m;
    x = [x1 x2];
    y = [y1 y2];
    semilogy(x,y);
    hold on
end
legend("m=1","m=2","m=3","m=4","m=5","m=6");
figure
%finestra con sottofinestre
for m=1:6
    x1 = linspace(-m,0);
    x2 = linspace(0,m);
    y1 = (m-x1.^2./m).^m;
    y2 = (x2.^2./m+m).^m;
    x = [x1 x2];
    y = [y1 y2];
    subplot(3,3,m);
    semilogy(x,y);
    title("m = "+m);

end




