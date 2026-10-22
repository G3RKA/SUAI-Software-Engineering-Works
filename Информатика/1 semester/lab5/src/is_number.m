function [ answer ] = is_number( request )
    %negative_number Проверяет, подходит ли введённое данное под число
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
        answer = is_number(request);
    end
    answer = str2double(answer);
    if isnan(answer)
        disp('Ошибка!')
        disp('Данные содержат символ или пробел!')
        answer = is_number(request);
    end
end

