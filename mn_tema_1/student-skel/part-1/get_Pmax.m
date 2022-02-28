function [array] = get_Pmax(rows)
  var = floor((rows*(rows+1))/2);
  array = zeros(1,var);
  k=1;
  
  for i = 1:rows-1
    for j = 1:i
      array(k) += i+1;
      k++;
    endfor
  endfor
  
  for i = 1:rows
    array(k)=1;
    k++;
  endfor
  endfunction