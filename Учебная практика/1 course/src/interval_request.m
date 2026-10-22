function [ Xmin, Xmax, dx ] = interval_request(dx_need)
%Функция запрашивает интервал и проверяет его на корректность
%   Xmin, Xmax - Левая и правая границы интервала
Xmin = number_request('Введите левую границу: ');
Xmax = number_request('Введите правую границу: ');
dx = 1;
if dx_need
    dx = number_request('Введите шаг: ');
end
if Xmin > Xmax
    disp('Левая граница больше правой')
    [Xmin, Xmax, dx] = interval_request(dx_need);
    return
elseif Xmin == Xmax
    disp('Левая граница равна правой')
    [Xmin, Xmax, dx] = interval_request(dx_need);
    return
elseif ((Xmax - Xmin) < dx) && dx_need
    disp('Шаг больше промежутка')
    [Xmin, Xmax, dx] = interval_request(dx_need);
    return
end
end

