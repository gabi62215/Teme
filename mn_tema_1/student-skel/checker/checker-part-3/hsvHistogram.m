function [sol] = hsvHistogram(path_to_image, count_bins)
  
  im = hsv_to_rgb(path_to_image);

  matrix_lines = size(im);
  
  h = im(:,:,1);
  s = im(:,:,2);
  v = im(:,:,3);
     
  i = 0;
  while i<count_bins+1
    binrange(i+1) = i*1.01/count_bins;
    binrange(i+2) = i*1.01/count_bins + 1.01/count_bins;
    i += 2;
    
  endwhile
  
  binrange(end) = [];
  
  binrange_lines = size(binrange);
  h_histo = zeros(1,binrange_lines(2));
  s_histo = zeros(1,binrange_lines(2));
  v_histo = zeros(1,binrange_lines(2));
  
  
  for i = 1:matrix_lines(1)
    h_h = histc(h(i,:),binrange);
    s_h = histc(s(i,:),binrange);
    v_h = histc(v(i,:),binrange);
    h_histo += h_h;
    s_histo += s_h;
    v_histo += v_h;
  endfor
  
  sol = [h_histo s_histo v_histo];
  sol_size = size(sol);
  %find all the bins of scalar value
  for i = 1:sol_size(2)
    if mod(i,(count_bins+1))==0
      sol(i) = -1;
    endif
  endfor
  
  i=1;
  %delete found bins
  sol(sol<0) = [];
 
    
    
endfunction
  