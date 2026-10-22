function [ x_s ] = SLAU_Solution( A, B )
%Нахоидт корни СЛАУ методом LU разложения
%       A - Коэффициенты 
%       B - Свободные члены
%       x_s - Корни уравнения
U = upper_matrix(A);
L = lower_matrix(A);

n = size(A, 2);

for i=2:n
    U = U_calc(A, L, U, i);
    L = L_calc(A, L, U, i);
end

x_s = calc_matrix(U , calc_matrix(L, B, false), true);

end

