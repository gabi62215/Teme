function [Q R] = Householder(A)
	%Intrari: A = matricea sistemului
	% b = vectorul coloana al termenilor liberi
	% Q = matricea ortogonala
	% R = matricea superior triunghiulara
	% Pentru verificare Q*R 
	[m n] = size(A);
	Q = eye(m);
	
	for p = 1 : min(m-1,n)
		sigma = -norm(A(p:m, p));
		if A(p, p) < 0
			sigma = -sigma;
		end;

		% calculare reflector Householder
		vp(1:m, 1) = 0;
		vp(p) = A(p, p) + sigma;
		vp(p + 1:m) = A(p + 1:m, p);
    
		beta = sigma * vp(p);
	
		if beta ~= 0
      % transformare coloana p din Ap
      A(p, p) = -sigma;
		  A(p + 1:m, p) = 0;
		  
      %transformare coloanele p+1:n din Ap
      for j = p + 1 : n
		    t = vp(p:m)' * A(p:m, j) / beta;
		    A(p:m, j) = A(p:m, j) - t * vp(p:m);
		  end;
	
  	  %transformare coloanele 1:n din H
		  for j = 1:m
		    t = vp(p:m)' * Q(p:m, j) / beta;
		    Q(p:m, j) = Q(p:m, j) - t * vp(p:m);
		  end;
     end
  end;
  
	R = A;
	Q = Q';
endfunction