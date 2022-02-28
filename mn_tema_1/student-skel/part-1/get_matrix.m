function [matrix] = get_matrix(rows)
  
  var = floor((rows*(rows+1))/2);
  left_matrix = get_left_matrix(rows);
  right_matrix = left_matrix';
  up_matrix = get_up_matrix(rows);
  down_matrix = up_matrix';
  
  matrix = left_matrix+right_matrix+up_matrix+down_matrix;
  
  links = get_links(rows);
  
  for i = 1:var
    matrix(i,i)=links(i);
    for j = 1:var
      if i!=j && matrix(i,j)!=0
        matrix(i,j) -= 2;
      endif
    endfor
  endfor
  
  
endfunction