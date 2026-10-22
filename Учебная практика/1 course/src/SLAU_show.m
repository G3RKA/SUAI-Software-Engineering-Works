function SLAU_show(A, B)
%Функция показывает СЛАУ в привычном виде
%   А - Коэффициенты
%   B - Свободные члены
str = '';
for i=1:size(A,1)
    for j=1:size(A,2)
        if A(i,j) ~= 0
            str_elem_pres = num2str(A(i,j));
            if A(i,j) ~= 1
                str = strcat(str,str_elem_pres);
                str = strcat(str,'*x');
            else
                str = strcat(str,'x');
            end
            num = num2str(j);
            str = strcat(str,num);
            if (j~=size(A,2))
                str_elem_fur = num2str(A(i,j+1));
                if (str_elem_fur(1) ~= '-') && (str_elem_fur(1) ~= '0')
                    str = strcat(str,'+');
                end
            end
        end
    end
    str = strcat(str,'=',num2str(B(i,1)));
    disp(str)
    str = '';
end

end

