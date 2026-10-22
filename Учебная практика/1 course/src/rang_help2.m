function [ count ] = rang_help2( A )
%Функция считает кол-во ненулевых строк в А
%   А - матрица
n = size(A,1);
num = size(A,2);

count = 0;

for i = 1:n
    for j = i:num
        if ((A(i,j) ~= 0) || (A(i,j) ~= -0))
            count = count + 1;
            break
        end
    end
end

end

