function [centroids] = intialize_clusters(points,NC)
  
  D = size(points);
  centroids=zeros(NC,D(2));
  indice = 0;
  for j = 1:NC
    i=1;
    while i>0
      indice = j+((i-1)*NC);
      if indice > D(1)
        break;
      endif
      centroids(j,:) = centroids(j,:) + points(indice,:);
      i++;
      
    endwhile
   
    centroids(j,:) = centroids(j,:)/(i-1);
    
  endfor
endfunction