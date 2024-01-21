#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include <malloc.h>
#include <alloca.h>

#define OK 0
#define ERR 1


#if OK == ERR
Неопределённое поведение
Что такое побочный эффект?
• Свойство в определённых маргинальных ситуациях выдавать результат, зависящий от реализации компилятора (библиотеки, микросхемы)
и случайных факторов наподобие состояния памяти или сработавшего прерывания.
Какие выражения стандарт c99 относит к выражениям с побочным эффектом?
• Модификация данных.
• Обращение к переменным, объявленным как volatile.
• Вызов системной функции, которая производит побочные эффекты (например, файловый ввод или вывод).
• Вызов функций, выполняющих любое из вышеперечисленных действий.
Почему порядок вычисления подвыражений в языке Си неопределен?
Для возможности разработчикам компилятора делать оптимизации кода

Порядок вычисления каких выражений в языке Си определен?
• Логическая конъюнкция, логическая дизъюнкция, “запятая”, тернарный оператор
Что такое точка следования?
• Точка следования – это точка в программе, в которой программист знает какие выражения (или подвыражения) уже вычислены,
а какие выражения (или подвыражения) еще нет.
Какие точки следования выделяет стандарт c99?
• Между вычислением левого и правого операндов в операциях &&, || и ",".
• Между вычислением первого и второго или третьего операндов в тернарной операции.
Почему необходимо избегать выражений, которые дают разный результат в зависимости от порядка их вычисления?
• Не гарантирует полной совместимости различных реализаций языка. Нельзя заранее знать, какой результат будет получен.
Какие виды "неопределенного" поведения есть в языке Си?
• Unspecified behavior (неспецифированное поведение):
int a = 5;
printf("%d %d\n", a++, a++);
• • Стандарт предлагает несколько вариантов на выбор. Компилятор может реализовать любой вариант. При этом на вход компилятора подается корректная программа.
• Implementation-defined behavior (поведение, определённое реализацией):
printf("The size of int is %d bytes\n", sizeof(int)); // Здесь размер типа int зависит от конкретной реализации компилятора и целевой платформы.
• • Похоже на неспецифицированное  (unspescified) поведение, но в документации к компилятору должно быть указано, какое именно поведение реализовано.
• Undefined behavior (собст. неопределённое поведение):
int x = 5;
int y = 0;
int z = x / y;
• • Такое поведение возникает как следствие неправильно написанной программы или некорректных данных.
• • Стандарт ничего не гарантирует, может случиться все что угодно
Почему "неопределенное" поведение присутствует в языке Си?
• освободить разработчиков компиляторов от необходимости обнаруживать ошибки, которые трудно диагностировать.
• избежать предпочтения одной стратегии реализации другой.
• отметить области языка для расширения языка (language extension).
Какой из видов "неопределенного" поведения является самым опасным? Чем он опасен?
• Самым опасным является “undefined behaviour”, так как при его возникновении может получиться абсолютно любой результат,
от разрушения стека до аварийного завершения программы. 

Как бороться с неопределенным поведением?
• Избегать сложных выражений
• Включайте все предупреждения компилятора, внимательно читайте их. 
• Используйте возможности компилятора (-ftrapv).
• Используйте несколько компиляторов.
• Используйте статические анализаторы кода (например, clang).
• Используйте инструменты такие как valgrind, Doctor Memory и др.
• Используйте утверждения.
Приведите примеры неопределенного поведения.
• Использование неинициализированных переменных.
int x;
int y = x + 5;
printf("%d\n", y);
• Переполнение знаковых целых типов.
int x = INT_MAX;
printf("%d\n", x + 1);
• Выход за границы массива.
int arr[3] = {1, 2, 3};
printf("%d\n", arr[3]);
• Использование «диких» указателей.
int *ptr;
*ptr = 10;
printf("%d\n", *ptr);
Приведите примеры поведения, зависящего от реализации.
• результат x % y, где x и y целые, а y отрицательное, может быть как положительным, так и отрицательным.
• Битовый сдвиг знаковых (сдвиг знакового числа вправо может заполнять освободившиеся биты знаковым битом, а в других - нулями)
Приведите примеры неспецифицированного поведения.
• все аргументы функции должны быть вычислены до вызова функции, но они могут быть вычислены в любом порядке.
#endif

#ifdef OK // Функции

#endif




int main(void)
{
    return OK;
}