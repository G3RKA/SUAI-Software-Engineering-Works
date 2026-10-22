function [ A, B] = request_double_matrix()
%Запрашивает матрицы коэффициентов и свободных членов построчно
A = [];
B = [];
n = number_request('Введите количество уравнений в системе: ');
if (n < 2)
    disp('Неверный ввод')
    SLAU_wait();
    request_double_matrix();
    return;
end

for i = 1:n
   stroka = ['Уравнение ' num2str(i)];
   disp(stroka)
   for j = 1:n+1 
       if j > n
           stroka = ['Введите свободный член ' num2str(i) ': '];
           num = number_request(stroka);
           B(i,1) = num;
       else
           stroka = ['Введите коэффициент ' num2str(j) ': '];
           num = number_request(stroka);
           A(i,j) = num;
       end

   end
end
end

