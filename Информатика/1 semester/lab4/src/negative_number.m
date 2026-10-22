function [ answer ] = negative_number( request )
    %negative_number Проверяет, отрицально ли число
    %   Аргументы:
    %       request - Строка. Будет показана при запросе числа
    %   Вывод:
    %       answer - Строка. Вывод введённого числа, если оно удовлетворяет
    %       условию.
    answer = input(request, 's');
    if strfind(answer,',')
        disp('Ошибка!')
        disp('Данные содержат запятую!')
        disp('Используйте точку, вместо запятой!')
        answer = negative_number(request);
        return 
    end
    answer = str2double(answer);
    if isnan(answer)
        disp('Ошибка!')
        disp('Данные содержат символ или пробел!')
        answer = negative_number(request);
        return 
    elseif answer >=0
        disp('Ошибка!')
        disp('Введите отрицательное число!')
        answer = negative_number(request);
        return 
    end
end

