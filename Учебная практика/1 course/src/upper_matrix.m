function [ U ] = upper_matrix( A )
%Функция выделяет верхнеугольную матрицу из А
%   А - Исходная матрица
n = size(A, 2);

U = A;

count = 1;
for i=1:n
   for j = 1:n
       if j == count
           U(j,i) = 1;
       elseif j>count
           U(j,i) = 0;
       else
           U(j,i) = A(j,i);
       end
   end
   count = count + 1;
end

