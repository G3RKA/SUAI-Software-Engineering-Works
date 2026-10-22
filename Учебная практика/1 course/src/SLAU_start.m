function SLAU_start
% Данные по варианту
%A = [2 8 7 10;5 8 2 4;5 3 2 6;7 7 5 3];
%B = [17.8; 10.5; 10.1; 12.7];
clc
clear
close
disp('Работа с данными пользователя.')
disp('Введите пункт для загрузки матрицы:');
disp('1. Загрузить файл .mat*');
disp('2. Ручной ввод');
disp('3. Отмена ');
disp('*Примечание:');
disp('Должна быть матрицы А(коэффициенты) и В(свободные члены)');
file = input('Способ ', 's');

if file == '2'
    [A, B] = request_double_matrix();
elseif file == '1'
    str = input('Введите название файла для загрузки: ','s');
    m = fopen(strcat(str,'.mat'));
    while m == -1
        disp('Файла не существует')
        disp('Для перехода обратно введите not');
        str = input('Введите название файла для загрузки: ','s');
        if str == 'not'
            SLAU_start;
            break;
        end
        m = fopen(strcat(str,'.mat'));        
    end
    fclose(m);
    m = matfile(strcat(str,'.mat'));
    A = m.A;
    B = m.B;
elseif file == '3'
    SLAU_lobby;
    return;
else
    SLAU_start;
    return;
end



if size(A, 2) ~= size(B, 1)
    disp('Матрицы разного размера!');
    SLAU_wait;
    SLAU_start;
    return
elseif size(A, 1) ~= size(A, 2)
    disp('Матрица коэффициентов неквадратная!');
    SLAU_wait;
    SLAU_start;
    return
end

rank_A = rang(A);
rank_AB = rang([A B]);

if rank_A == rank_AB
   if rank_A < size(A,1)
        disp('СЛАУ имеет бесконечное количество решений!');   
        SLAU_wait;
        SLAU_start;
        return
   end
else
    disp('СЛАУ несовместна!');   
    SLAU_wait;
    SLAU_start;
    return
end

if (deter(A)) == 0 || isnan(deter(A))
    disp('СЛАУ не имеет решений!');
    SLAU_wait;
    SLAU_start;
    return
end

A = Fix_diag_zeros(A);

f1 = @() SLAU_Solution(A, B);
x = f1();

f2_1 = @() lu(A);
[L,U] = f2_1();
f2_2 = @() U \ (L \ B);
x_better = f2_2();

disp('Заданная СЛАУ: ');
SLAU_show(A,B);
disp('Корни СЛАУ по разработанной функции: ');
X_show(x)
disp('Корни СЛАУ по функции lu: ');
X_show(x_better)

warning('off','all')
disp('Время вычисления по разработанной функции: ');
fprintf('  %-15.10f \n',  timeit(f1));
disp('Время вычисления по функции lu: ');
fprintf('  %-15.10f \n',  timeit(f2_1)+timeit(f2_2));
warning('on','all')

disp('Нажмите любую кнопку для продолжения ')
input('');
SLAU_lobby;
end
