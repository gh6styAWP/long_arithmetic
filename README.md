# long_arithmetic

Задание: По двум заданным пользователем с клавиатуры длинным числам определить результат арифметических операций с ними. 
Хранение длинных чисел предусмотреть в виде десятичного дополнительного кода. 
При организации деления осуществлять все необходимые проверки определенности результата. 
При разработке программы отдельными функциями должны быть оформлены: 
- считывание и формирование в памяти длинного числа;
- вывод на экран длинного числа;
- смена знака длинного числа;
- умножение двух длинных чисел;
- сложение двух длинных чисел;
- целочисленное деление длинных чисел: реализовать имитацией деления столбиком.

Релиз: Хранение длинных чисел не реализовано в виде дополнительного кода, вместо этого они хранятся как векторы символов, где каждое число представлено 
в виде символа. Не реализована функция смены знака. 

Преимущества: 
- Проще реализовать.
- Явное представление знака числа с использованием символа '-', что интуитивно понятно.
Недостатки:
- Сложнее для расширения, если потребуются сложные операции, такие как вычисления в фиксированной разрядности с представлением отрицательных чисел.
- Отсутствие преимуществ, которые предоставляет десятичный дополнительный код для некоторых операций с фиксированной точностью.
