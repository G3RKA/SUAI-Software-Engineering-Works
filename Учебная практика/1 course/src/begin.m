while true
clc
clear
close
disp('Главное меню.');
disp('Введите номер пункта:');
disp('1. Решение нелинейных и трансцендентных уравнений');
disp('2. Решение СЛАУ ');
disp('3. Информация о программе и авторе ');
disp('4. Выход ');

point = input('Пункт ', 's');

if point == '1'
    equation_lobby;
elseif point == '2'
    SLAU_lobby;
elseif point == '3'
    author_lobby;
elseif point == '4'
    disp('Работа программы завершена.');
    break
else
    begin;
    break;
end

end
