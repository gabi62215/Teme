function [hsv] = hsv_to_rgb(path_to_image)
  im = imread(path_to_image);
  dim = size(im);
  im = double(im);
  hsv = zeros(dim(1),dim(2),dim(3));
  hsv = double(hsv);
  
  h = hsv(:,:,1);
  s = hsv(:,:,2);
  v = hsv(:,:,3);
  h = double(h);
  s = double(s);
  v = double(v);
  
  red = im(:,:,1);
  green = im(:,:,2);
  blue = im(:,:,3);
  red = double(red);
  green = double(green);
  blue = double(blue);
  
  red = double(red/255);
  green = double(green/255);
  blue = double(blue/255);
  
  for i = 1:dim(1)
    for j = 1:dim(2)
      rgb = [red(i,j) green(i,j) blue(i,j)];
      MAX = max(rgb);
      MIN = min(rgb);
      delta = double(MAX - MIN);
      if delta == 0
        h(i,j) = 0;
      else
        if MAX==red(i,j)
          h(i,j) = double(60*mod((green(i,j)-blue(i,j))/delta,6));
        endif
        if MAX==green(i,j)
          h(i,j) = double(60*(2+(blue(i,j)-red(i,j))/delta));
        endif
        if  MAX==blue(i,j)
          h(i,j) = double(60*(4+(red(i,j)-green(i,j))/delta));
        endif
      endif 
      
      h(i,j) = double(h(i,j)/360);
      
      if MAX==0 
        s(i,j) = 0;
      else
        s(i,j) = double(delta/MAX);
      endif
     
      
      v(i,j) = MAX;
      
    endfor
  endfor
  
  hsv(:,:,1)=h;
  hsv(:,:,2)=s;
  hsv(:,:,3)=v;
  
endfunction
        
      
      