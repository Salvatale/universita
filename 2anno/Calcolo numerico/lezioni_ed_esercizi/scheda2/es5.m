A = diag(ones(9,1)*-2) + diag(ones(8,1),1) + diag(ones(8,1),-1)
vec = A(3,:);
A(3,:) = A(6,:)
A(6,:) = vec
vec = A(:,1);
A(:,1) = A(:,4)
A(:,4) = vec