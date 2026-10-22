function [ step ] = step_req(num1, num2)
    %step_req Запрашивает шаг интервала и проверяет его на корректность
    %   Аргументы:
    %       num1 - Число. Левая граница интервала
    %       num2 - Число. Правая граница интервала
    %   Вывод:
    %       step - Число. Значение шага, если он введён правильно
    %       условию.
    step = input('Введите значение шага интервала ', 's');
    step = str2double(step);
    if isnan(step)
        disp('Ошибка!')
        disp('Данные содержат символ или пробел!')
        step = step_req(num1, num2);
        return
    elseif (num1 > num2) && (step>0)
        disp('Ошибка!')
        disp('Шаг для данных границ должен быть отрицателен!')
        step = step_req(num1, num2);    
        return
    elseif (num1 < num2) && (step<0)
        disp('Ошибка!')
        disp('Шаг для данных границ должен быть положителен!')
        step = step_req(num1, num2);   
        return
    end
end

