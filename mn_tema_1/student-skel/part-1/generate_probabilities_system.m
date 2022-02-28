function [A, b] = generate_probabilities_system(rows)
  
  var = floor((rows*(rows+1))/2);
  A=get_matrix(rows);
  b=zeros(var,1);
  i=var;
  
  while i > var-rows
    b(i)=1;
    i--;
  endwhile
  
endfunction
    