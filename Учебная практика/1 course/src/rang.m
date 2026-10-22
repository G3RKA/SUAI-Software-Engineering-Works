function [count] = rang( A )
%Функция считает ранг матрицы А
%   А - матрица
B = A;
n = size(B,1);

i = 2;

while (B(1,1) == 0)
    B = swap(B, 1,i);
    i = i + 1;
    if i >= n
        break
    end
end

for i=1:n-1
    B = rang_help(B, i);
end

count = rang_help2(B);

end

