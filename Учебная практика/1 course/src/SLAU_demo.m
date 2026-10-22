function SLAU_demo
A = [2 8 7 10;5 8 2 4;5 3 2 6;7 7 5 3];
B = [17.8; 10.5; 10.1; 12.7];


f1 = @() SLAU_Solution(A, B);
x_s = f1();

f2_1 = @() lu(A);
[L,U] = f2_1();
f2_2 = @() U \ (L \ B);
x_s_b = f2_2();

disp('Заданная СЛАУ: ');
SLAU_show(A,B);

disp('Корни СЛАУ по разработанной функции: ');
X_show(x_s)
disp('Корни СЛАУ по функции lu: ');
X_show(x_s_b)

warning('off','all')
disp('Время вычисления по разработанной функции: ');
fprintf('  %-15.10f \n',  timeit(f1));
disp('Время вычисления по функции lu: ');
fprintf('  %-15.10f \n',  timeit(f2_1)+timeit(f2_2));
warning('on','all')

disp('Нажмите любую кнопку для продолжения ')
input('');
clear;
SLAU_lobby;

end