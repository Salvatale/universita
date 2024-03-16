

X = [-6:6];
c = [1 -6 11 -6];
r1 = roots(c);
plot(X,polyval(c,X));




z1=fzero(@(x) x.^3-6*x.^2+11*x-6,1.6);
z2=fzero(@(x) (x.^3-6*x.^2+11*x-6)./(x-z1),1.6);
z3=fzero(@(x) (x.^3-6*x.^2+11*x-6)./((x-z2).*(x-z1)),1.6);

x=1;
p2=x.^2-2*x+1;
format long e
z4=fzero(@(x) x.^2-2*x+1,0.8);

C2 = [1 -2 1];
roots(C2);


C3 = [1 -7 15 -13 4];
z5 = roots(C3)
polyval(C3,1)

[C4,R]=deconv(C3,[1 -z5(1)])
roots(C4)