function equation_lobby
clc
clear
close
disp('Решение нелинейных и трансцендентных уравнений.');
disp('Выберите дальнейшее действие.');
disp('Введите номер пункта:');
disp('1. Демонстрационный пример');
disp('2. Работа с данными пользователя ');
disp('3. Назад ');

point = input('Пункт ', 's');

if point == '1'
    equation_demo;
elseif point == '2'
    equation_start;
elseif point == '3'
    begin;
    return;
else
    equation_lobby;
    return;
end

end