function X_show(x_s)
%Функция показывает корни в читаемый вид
%   x_s - Матрица-вектор корней
for i=1:size(x_s,1)
    str = 'x';
    str = strcat(str,num2str(i));
    str = strcat(str,'=');
    str = strcat(str,num2str(x_s(i,1)));
    disp(str)
end

end



