function [ sum ] = sigma_sum(i,j, L, U, bool)
%Функция считает значение по формуле lu разложения
%   i,j - строка,столбец
%   L,U - матрицы LU разложения
%   bool - true(Формула для L) и false(Формула для U)

sum = 0;
if bool
    n = j-1;
else
    n = i-1;
end

for k=1:n
    sum = sum + L(i,k)*U(k,j); 
end

end

