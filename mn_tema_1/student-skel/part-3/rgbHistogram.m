function [sol] = rgbHistogram(path_to_image, count_bins)
  im = imread(path_to_image);
  matrix_lines = size(im);
  binrange = [];
  i=0;
  
  
  red = im(:,:,1);
  green = im(:,:,2);
  blue = im(:,:,3);
  
  while i<count_bins+1
    binrange(i+1) = i*256/count_bins;
    binrange(i+2) = i*256/count_bins + 256/count_bins;
    i += 2;
    
  endwhile
  
  binrange(end) = [];
  
  binrange_lines = size(binrange);
  r_histo = zeros(1,binrange_lines(2));
  g_histo = zeros(1,binrange_lines(2));
  b_histo = zeros(1,binrange_lines(2));
  
  
  for i = 1:matrix_lines(1)
    red_h = histc(red(i,:),binrange);
    green_h = histc(green(i,:),binrange);
    blue_h = histc(blue(i,:),binrange);
    r_histo += red_h;
    g_histo += green_h;
    b_histo += blue_h;
  endfor
  
  sol = [r_histo g_histo b_histo];
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