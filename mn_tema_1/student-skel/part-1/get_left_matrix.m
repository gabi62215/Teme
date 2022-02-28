function [matrix] = get_left_matrix(rows)
  validR = get_rows(rows);
  var = floor((rows*(rows+1))/2);
  matrix=zeros(var,var);
  c=0;
  Pmax = get_Pmax(var);
  
  for i = 1:var
    if validR(i) == 1
      matrix(i,Pmax(i)+c)=1;
      c+=1;
    endif
  endfor
endfunction