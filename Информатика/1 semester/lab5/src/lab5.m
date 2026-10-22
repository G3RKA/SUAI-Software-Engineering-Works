% Очистка консоли и рабочей области
clc;
clear;
% Запрос функции
fBody = input('Введите функцию: f(x) = ', 's');
f = eval(['@(x)' fBody]);
% Запрос интервала
int_min = is_number('Введите левую границу');
int_max = is_number('Введите правую границу');
if int_min > int_max
    [int_min, int_max] = swap(int_min, int_max);
end
% Значения для гладкая линия
% Построение интервала для гладкой линии
x = int_min:(abs(int_max)+abs(int_min))/999:int_max;
% Расчёт функции при "гладкой" линии
y = f(x);
for i = 1:length(x)
    z(i) = integral(f, int_min, x(i));
end
% Значения для 15 точек
x1 = int_min:(abs(int_max)+abs(int_min))/14:int_max;
% Расчёт функции для 15 точек
y1 = f(x1);
for i = 1:length(x1)
    z1(i) = integral(f, int_min, x1(i));
end
% Отрисовка таблицы Аргумент-функция-интеграл
table_draw(x1,y1,z1)
% Строительство графика
k = 2; % Коэффициент увеличения графика
subplot(1,2,1);
% График гладкий
plot(x,y,'Color', 'yellow', 'LineWidth', 1.25);
hold on
% График 15 точек
plot(x1,y1,'Color', 'yellow', 'LineWidth', 1.25, 'Marker', '+', 'MarkerEdgeColor', 'blue');
% График отметки минимального значения
plot([int_min, int_max], [min(y), min(y)],'--k')
% График отметки максимального значения
plot([int_min, int_max], [max(y), max(y)],'--k')
hold off
grid on
% Легенда
legend(fBody)
xlabel x
ylabel y

subplot(1,2,2);
% График гладкого интеграла
plot(x,z, 'Color', 'magenta', 'LineWidth', 1.5, 'LineStyle', '--');
hold on
% График 15 точек
plot(x1,z1, 'Color', 'magenta', 'LineWidth', 1.5, 'LineStyle', '--', 'Marker', '+', 'MarkerEdgeColor', 'blue');
% График отметки минимального значения
plot([int_min, int_max], [min(z), min(z)],'--k')
% График отметки максимального значения
plot([int_min, int_max], [max(z), max(z)],'--k')
hold off
grid on
% Легенда
legend(strcat('Интеграл 0->x f(x)= ', fBody))
xlabel x
ylabel z