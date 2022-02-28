function [centroids] = clustering_pc(points, NC)
  
  D = size(points);
  centroids = zeros(NC,D(2));
  
  centroids = intialize_clusters(points, NC,D(2));
  centroids_2=zeros(NC,D(2));
    
  iteration = 0;
  while 1
    c = cell(1,NC);
    euclidian=zeros(1,NC);
    for i = 1:D(1)
      %assign each point to the nearest centroid cluster
      min = inf;
      indice = 0;
      for j = 1:NC
        euclidian(j)=norm(centroids(j,:)-points(i,:));
        if min > euclidian(j)
          min = euclidian(j);
          indice = j;
        endif
      endfor
    
      c{1,indice}=[c{1,indice};points(i,:)];
    endfor
  
    allah = 0;
    for n = 1:NC
      %calculate new centroids 
      lines = size(c{1,n});
      centroids_2(n,:) = centroids(n,:);
      centroids(n,:) = zeros(1,D(2));
      
      for k = 1:lines(1)
        centroids(n,:) += c{1,n}(k,:);
      endfor
      
      centroids(n,:) = centroids(n,:)/k;
      if norm(centroids(n,:)-centroids_2(n,:)) <= 1e-5
        allah++;
      endif
    endfor
    %check to see if the new centroids are equal to the old ones and stop if so
    if allah == NC 
      break;
    endif
    
  endwhile
    
  
endfunction