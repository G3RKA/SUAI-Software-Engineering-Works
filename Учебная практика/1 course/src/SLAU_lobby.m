function SLAU_lobby
clc
clear
close
disp('Решение СЛАУ.');
disp('Выберите дальнейшее действие.');
disp('Введите номер пункта:');
disp('1. Демонстрационный пример');
disp('2. Работа с данными пользователя ');
disp('3. Назад ');

point = input('Пункт ', 's');

if point == '1'
    SLAU_demo;
elseif point == '2'
    SLAU_start;
elseif point == '3'
    begin;
    return;
else
    SLAU_lobby;
    return;
end

end