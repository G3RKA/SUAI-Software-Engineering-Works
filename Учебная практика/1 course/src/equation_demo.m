function equation_demo
Xmin = -2*pi;
Xmax = 2*pi;
dx = 1;
Epsilon = 1.0e-04;
fBody = '3*x-cos(x)-2';
func = eval(['@(x)' fBody]);
x_s = Xmin:dx:Xmax;
y_s = func(x_s);

f1 = @() equation_solution(Xmin, Xmax, func, Epsilon);
f2 = @() fzero(func, [Xmin Xmax]);
f1_otvet = f1();

hold on
grid on
plot(x_s,y_s,'LineWidth', 1.75);
legend('Графическое представление уравнения')
xlim([Xmin Xmax])
plot([Xmin Xmax],[0 0] , 'color', 'black');
xlabel x
ylabel y
plot(f1_otvet,0,'r.','MarkerSize', 20)

disp('Заданное уравнение: ');
fprintf('  %-15.10s \n',  strcat(fBody,'=0'));
disp('Левая граница интервала: ');
fprintf('  %-15.10f \n',  Xmin);
disp('Правая граница интервала: ');
fprintf('  %-15.10f \n',  Xmax);
disp('Корень уравнения на заданном промежутке по разработанной функции: ');
fprintf('  %-15.10f \n', f1_otvet);
disp('Корень уравнения на заданном промежутке по функции fzero: ');
fprintf('  %-15.10f \n', f2());
fprintf('Отличие между корнями: \n   %15.15f \n',  abs(f2() - f1()));
disp('Время вычисления по разработанной функции: ');
fprintf('  %-15.10f \n',  timeit(f1));
disp('Время вычисления по функции fzero: ');
fprintf('  %-15.10f \n',  timeit(f2));

disp('Нажмите любую кнопку для продолжения ')
input('');
equation_lobby;
end
