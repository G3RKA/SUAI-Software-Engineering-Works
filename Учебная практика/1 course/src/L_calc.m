function [ L ] = L_calc(A, L, U, n )
%Функция выделяет n столбец для L матрицы из А по формуле lu разложения
%   А - Матрица Коэффициентов
%   L - Текущая L матрица
%   U - U матрица
%   n - столбец где производится расччёт
for i=1:size(A, 2);
    if L(i,n) == 0 
        continue
    end
    L(i,n) = (A(i,n) - sigma_sum(i, n, L, U, true) );
end

end
