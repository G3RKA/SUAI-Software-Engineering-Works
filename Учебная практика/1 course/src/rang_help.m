function [ A ] = rang_help( A, num )
%Функция работает по столбцу n и обнуляет столбец по неким элементом для
%получения треугольной матрицы
%   А - матрица 
%   num - столбец
n = size(A,1);

i = num;
while A(i,num) == 0
    A = swap(A,num,i);
    i = i + 1;
    if i >= n
        break
    end
end
A = swap(A,num,i);

for j = num+1:n
    mnoj = A(j,num)/A(num,num);
    for h = num:size(A,2);
        A(j,h) = A(j,h)+(-1)*mnoj*A(num,h);
    end
end

end

