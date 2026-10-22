function [ x_new ] = equation_solution(Xmin, Xmax, func, Epsilon)
    %Находит локальный корень данного уравнения методом хорд
    %       Xmin - Число. Левая граница промежутка
    %       Xmax - Число. Правая граница промежутка
    %       func - Функция. Само уравнение
    %       Epsilon - Число. Погрешность подсчёта корня
    %       x_new - Число. Посчитанный корень

    if (func(Xmin) * func(Xmax)) > 0 
        x_new = 'NO_SOL';
        return;
    end 

    x_old = Inf;
    x_new = 0;
    while abs(x_new-x_old) >= Epsilon
        x_old = x_new;
        x_new = Xmin - (((Xmax-Xmin)*func(Xmin))/(func(Xmax)-func(Xmin)));
        Xmin = x_new;
    end
end