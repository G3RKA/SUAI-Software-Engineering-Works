function [ U ] = U_calc(A, L, U, n )
%Функция выделяет n столбец для U матрицы из А по формуле lu разложения
%   А - Матрица Коэффициентов
%   L - L матрица
%   U - Текущая U матрица
%   n - столбец где производится расччёт
for i=1:size(A, 2);
    if U(i,n) == 1 
        break
    end
    U(i,n) = 1/L(i,i)*(A(i,n) - sigma_sum(i, n, L, U, false) );
end

end

