# Тесты для лабораторной работы №3 (задание lab_03_01_01)

## Входные данные
int a[N][M] - матрица из N (N<=10) строк и из M (M<=10) столбцов

## Выходные данные
int b[N] - массив, в котором каждый k-ый элемент равен 1, если k-ая строка
исходной матрицы симметрична и 0, если не симметрична.

# Позитивные тесты: 
- 01 - обычный тест (квадратная матрица, присутствуют симметричные строки)
- 02 - все строки квадратной матрицы симметричны
- 03 - все строки квадратной матрицы не симметричны
- 04 - обычный тест (не квадратная матрица, присутствуют симметричные строки)
- 05 - все строки не квадратной матрицы симметричны
- 06 - все строки не квадратной матрицы не симметричны
- 07 - матрица состоит из одного элемента

# Негативные тесты:
- 01 - Ошибка ввода (ничего не введено)
- 02 - Ошибка ввода (отрицательное n)
- 03 - Ошибка ввода (нулевое n)
- 04 - Ошибка ввода (отрицательное m)
- 05 - Ошибка ввода (нулевое m)
- 06 - Ошибка ввода (буква вместо цифры в n)
- 07 - Ошибка ввода (буква вместо цифры в m)
- 08 - Ошибка ввода (буква вместо цифры в элементе матрицы)
- 09 - Ошибка ввода (введено недостаточное кол-во элементов)
