function equation_start
clc
clear
close
disp('Работа с данными пользователя.')
disp('Введите данные для графика.')
fBody = input('Введите функцию: f(x) = ', 's');
try 
    func = eval(['@(x)' fBody]);
    func(0);
catch
    disp('Введено некоректное значение.')
    SLAU_wait;
    equation_start;
end
[Xm, Xmx, dx] = interval_request(true);


x_s = Xm:dx:Xmx;
y_s = func(x_s);
hold on
grid on
plot(x_s,y_s,'LineWidth', 1.75);
legend('Графическое представление уравнения')
xlim([Xm Xmx]);
plot([Xm Xmx],[0 0] , 'color', 'black');
xlabel x
ylabel y

disp('Введите промежуток поиска корня.')
[Xmin, Xmax] = interval_request(false);

plot([Xmin Xmin],[min(y_s) max(y_s)], 'color', 'green', 'LineStyle', '--');
plot([Xmax Xmax],[min(y_s) max(y_s)], 'color', 'green', 'LineStyle', '--');

Epsilon = input('Введите погрешность: ');

y = @() equation_solution(Xmin, Xmax, func, Epsilon);
y_otvet = y();

if y_otvet == 'NO_SOL'
   disp('Корней нет/Невозможно решить методом хорд.');
   disp('Нажмите любую кнопку для продолжения ')
   input('');
   equation_lobby;
   return;
end

plot(y(),0,'r.','MarkerSize', 20)

y1 = @() fzero(func, [Xmin Xmax]);
y1_otvet = y1();

disp('Корень уравнения на заданном промежутке по разработанной функции: ');
fprintf('   %15.15f \n',  y_otvet);
disp('Корень уравнения на заданном промежутке по функции fzero: ');
fprintf('   %15.15f \n',  y1_otvet);
fprintf('Отличие между корнями: \n   %15.15f \n',  abs(y1_otvet - y_otvet));
disp('Время вычисления по разработанной функции: ');
fprintf('  %-15.10f \n',  timeit(y));
disp('Время вычисления по функции fzero: ');
fprintf('  %-15.10f \n',  timeit(y1));

disp('Нажмите любую кнопку для продолжения ')
input('');
equation_lobby;
end
