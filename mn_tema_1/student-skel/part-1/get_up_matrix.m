function [matrix] = get_up_matrix(rows)
  
  var = floor((rows*(rows+1))/2);
  matrix=zeros(var,var);
  Pmax=get_Pmax(rows);
  rD=0:(var-1);
  
  for i = 1:(var-rows)
    matrix(i,Pmax(i)+rD(i))=1;
    matrix(i,Pmax(i)+rD(i)+1)=1;
  endfor
endfunction  
  