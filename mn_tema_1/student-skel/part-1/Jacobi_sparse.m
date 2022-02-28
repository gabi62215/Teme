function [x] = Jacobi_sparse(G_values, G_colind, G_rowptr, c, tol)  
  n = size(G_rowptr)-1;
  y = zeros(n(2),1);
  
  i = 2;
  x = zeros(n(2),1);
 
  
  while i>0
    x = csr_multiplication(G_values, G_colind, G_rowptr, y)+c;
    i++;
   
    if norm(x-y)<tol 
      break;
    endif
    
    y = x;
  endwhile
  
  
endfunction