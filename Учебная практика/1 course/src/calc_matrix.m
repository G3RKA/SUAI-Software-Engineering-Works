function [ y ] = calc_matrix( A, B, reversed )
%Функция считает систему вида верхнеугольной/нижнеугольной матрицы
%   A - матрица коэффициентов для системы
%   B - матрица свободных членов для системы
%   reversed - Система идёт сверху (L матрица)(false) или снизу (U матрица)(true)
stroka_n = size(A,1);
stolb_n = size(A,2);

y = B;

for i = 1:stroka_n
    y(i,1) = 1;
end

if not(reversed)
    min_i = 1;
    min_j = 1;
    max_i = stroka_n;
    max_j = stolb_n;
    dx = 1;
else
    min_i = stroka_n;
    min_j = stolb_n;
    max_i = 1;
    max_j = 1;
    dx = -1;
end

for i=min_i:dx:max_i
    s = B(i,1);

    for j = min_j:dx:max_j
        if (i == j) 
            continue
        else
            s = s+(-1)*A(i,j)*y(j,1);
        end
    end

    y(i,1) = s/A(i,i);
end

end

