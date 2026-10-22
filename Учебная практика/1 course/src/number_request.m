function [ answer ] = number_request( request )
    %Запрашивает целое число и проверяет на корректность
    %       request - Будет показана при запросе числа
    %       answer - Вывод введённого числа, если оно удовлетворяет
    %       условию.
    answer = input(request, 's');
    if strfind(answer,',')
        disp('Ошибка!')
        disp('Данные содержат запятую!')
        answer = number_request(request);
        return;
    end        
    answer = str2double(answer);
    if isnan(answer)
        disp('Ошибка!')
        disp('Данные содержат символ или пробел!')
        answer = number_request(request);
        return;
    end
end


