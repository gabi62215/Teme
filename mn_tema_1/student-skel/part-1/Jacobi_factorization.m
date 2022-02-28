function [G_J, c_J] = Jacobi_factorization(A, b)
  size = size(A);
  D = zeros(size(1));
  L = zeros(size(1));
  U = zeros(size(1));
  
  for i = 1:size(1)
    D(i,i) = A(i,i);
    for j = 1:size(2)
      if i<j
        U(i,j) = A(i,j);
      endif
      if i>j
        L(i,j) = A(i,j);
      endif
    endfor
  endfor
  
  D_1 = inv(D);
  
  G_J = D_1*(L+U);
  
  G_J = G_J * (-1);
  
  c_J = D_1*b;

endfunction
  
  
  
  