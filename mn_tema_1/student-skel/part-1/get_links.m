function [array] = get_links(rows)
  var = floor((rows*(rows+1))/2);
  array = zeros(1,var);
  array(1) = 4;
  
  for i = 2:rows
    varI = floor((i-1)*i)/2;
    array(varI+1) = 5;
    array(varI+i) = 5;
    
    if i!=2
      for j = 2:i-1
        array(varI+j) = 6;
      endfor
    endif
    
    if i == rows
      for j = 1:i
        array(varI+j) -= 1;
      endfor
    endif
    
    
    
    
   
  endfor
endfunction
  