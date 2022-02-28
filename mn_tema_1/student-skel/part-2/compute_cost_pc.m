function [cost] = compute_cost_pc(points, centroids)
  
  cost = 0;
  D = size(centroids);
  c = cell(1,D(1));
  [centroids c] = clustering_pc_2(points,D(1));
  for i = 1:D(1)
    lines = size(c{1,i});
    for j = 1:lines(1)
      cost += norm(centroids(i,:) - c{1,i}(j,:));
    endfor
  endfor
endfunction
  