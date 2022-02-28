function [array] = get_rows(r)
  array = [0];
    for i=1:r-1
      for j=1:i
        array(end+1)=1;
      endfor
      array(end+1)=0;
    endfor
endfunction