function [values, colind, rowptr] = matrix_to_csr(A)
  nz = length(A(A ~= 0));
  colind = zeros(1,nz);
  values = zeros(1,nz);
  rowptr = zeros(1,size(A,2));
  rowptr(1) = 1;

  counter = 1;
  for r = 1:size(A,2)
      for c = 1:size(A,1)
          if A(r,c) != 0
            colind(counter)=c;
            values(counter) = A(r,c);
            counter += 1;
          endif
      end
      rowptr(r+1) = counter;
  end
endfunction
    
    
              
    
    
    
         
            
    
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
    