function [ L ] = lower_matrix( A )
%Функция выделяет нижнеугольную матрицу из А
%   А - Исходная матрица
n = size(A, 2);

L = A;

count = 0;
for i=1:n
   for j = 1:n
       if j>count
           L(j,i) = A(j,i);
       else
           L(j,i) = 0;
       end
   end
   count = count + 1;
end

