function [ L ] = Fix_diag_zeros( L )
%Функция проверяет наличие нулей на диагоналях и в случае нахождения
%прибавляет строку к строке с нулём для его избавления
%L - L матрица для поиска нулей
%L - L матрица без нулей на диагоналях
n  = size(L,1);
for i=1:n-1
    if L(i,i) == 0
        elem = L(i,i);
        while elem == 0
            for j=1:n
                if L(j,i) ~= 0
                    elem = j;
                    break;
                end
            end
        end
        for j=1:n
            L(i,j) = L(i,j) + L(elem,j);
        end
    end
end


end

