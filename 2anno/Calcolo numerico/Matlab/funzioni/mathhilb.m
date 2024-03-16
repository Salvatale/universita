function [mat,detminori] = mathhilb(n)
%MATHHILB Summary of this function goes here
%   Detailed explanation goes here
mat = hilb(n);
for i=1:n
    detminori(i) = det(mat(1:i,1:i));
end

