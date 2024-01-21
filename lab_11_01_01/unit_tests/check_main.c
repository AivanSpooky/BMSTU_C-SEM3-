#include <check.h>
#include <stdio.h>
#include <limits.h>
#include "my_snprintf_impl.h"

// Строка
START_TEST(pos_1)
{
    int buf_size = 500;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Юнит-тесты - это боль...";

    int printed_target = snprintf(target_buf, buf_size, "%s", fmt);
    int printed_my = my_snprintf(buf, buf_size, "%s", fmt);

    ck_assert_str_eq(buf, target_buf);
    ck_assert_int_eq(printed_target, printed_my);
}
END_TEST

// Строка с \n в конце
START_TEST(pos_2)
{
    int buf_size = 500;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Слава Богу фанк-тестов нет!\n";

    int printed_target = snprintf(target_buf, buf_size, "%s", fmt);
    int printed_my = my_snprintf(buf, buf_size, fmt);

    ck_assert_str_eq(buf, target_buf);
    ck_assert_int_eq(printed_target, printed_my);
}
END_TEST

// Кавычки в строке
START_TEST(pos_3)
{
    int buf_size = 500;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "\\ \'Hello\", world!\n";

    int printed_target = snprintf(target_buf, buf_size, "%s", fmt);
    int printed_my = my_snprintf(buf, buf_size, fmt);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Строка с lld
START_TEST(pos_4)
{
    int buf_size = 500;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Проверим lld %lld\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, 1);
    int printed_my = my_snprintf(buf, buf_size, fmt, 1);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Несколько разных спецификаторов
START_TEST(pos_5)
{
    int buf_size = 500;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Вот тебе два числа: %lld %lld и строка: %s\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, 1, 2, "3");
    int printed_my = my_snprintf(buf, buf_size, fmt, 1, 2, "3");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Размер буфера равен строке Hello, world
START_TEST(pos_6)
{
    int buf_size = 13;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Hello, world! %lld %lld %s\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, 1, 2, "3");
    int printed_my = my_snprintf(buf, buf_size, fmt, 1, 2, "3");

    // printf("|%s|%s|\n", buf, target_buf);
    ck_assert_str_eq(buf, target_buf);
    ck_assert_int_eq(printed_target, printed_my);
}
END_TEST

// Размер буфера равен строке Hello, world!_ 
START_TEST(pos_7)
{
    int buf_size = 15;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Hello, world! %lld %lld %s\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, 1, 2, "3");
    int printed_my = my_snprintf(buf, buf_size, fmt, 1, 2, "3");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// В ходе теста должна вывестись первая цифра первого числа lld
START_TEST(pos_8)
{
    int buf_size = 16;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Hello, world! %lld %lld %s\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, 123, 2, "3");
    int printed_my = my_snprintf(buf, buf_size, fmt, 123, 2, "3");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// В ходе теста должна вывестись первая и вторая цифры первого числа lld
START_TEST(pos_9)
{
    int buf_size = 17;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Hello, malloc %lld %lld %s\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, 123, 2, "3");
    int printed_my = my_snprintf(buf, buf_size, fmt, 123, 2, "3");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// В ходе теста должно вывестись все первое число lld
START_TEST(pos_10)
{
    int buf_size = 18;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Hello, world! %lld %lld %s\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, 123, 123, "3");
    int printed_my = my_snprintf(buf, buf_size, fmt, 123, 123, "3");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// В ходе теста должно вывестись все первое число lld и пробел после него
START_TEST(pos_11)
{
    int buf_size = 19;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Hello, world! %lld %lld %s\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, 123, 123, "3");
    int printed_my = my_snprintf(buf, buf_size, fmt, 123, 123, "3");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод первой строки
START_TEST(pos_12)
{
    int buf_size = 16;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "Hello, world! %s %lld %s\n";

    int printed_target = snprintf(target_buf, buf_size, fmt, "c", 198, "123");
    int printed_my = my_snprintf(buf, buf_size, fmt, "c", 198, "123");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Попытка вывести строку через спецификатор (размер буфера больше предполагаемого)
START_TEST(pos_13)
{
    int buf_size = 16;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%s";

    int printed_target = snprintf(target_buf, buf_size, fmt, "123");
    int printed_my = my_snprintf(buf, buf_size, fmt, "123");

    //printf("|%s|%s|\n", buf, target_buf);
    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Попытка вывести строку через спецификатор (строка состоит из 1ого символа)
START_TEST(pos_14)
{
    int buf_size = 16;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%s";

    int printed_target = snprintf(target_buf, buf_size, fmt, "a");
    int printed_my = my_snprintf(buf, buf_size, fmt, "a");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод минимально возможного числа INT64
START_TEST(pos_15)
{
    int buf_size = 21;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, INT64_MIN);
    int printed_my = my_snprintf(buf, buf_size, fmt, INT64_MIN);

    // printf("|%s|%s|\n", buf, target_buf);
    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод значения, близкого к минимально возможному числу INT64
START_TEST(pos_16)
{
    int buf_size = 21;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, INT64_MIN + 1);
    int printed_my = my_snprintf(buf, buf_size, fmt, INT64_MIN + 1);

    // printf("|%s|%s|\n", buf, target_buf);
    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод максимально возможного числа INT64
START_TEST(pos_17)
{
    int buf_size = 21;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, INT64_MAX);
    int printed_my = my_snprintf(buf, buf_size, fmt, INT64_MAX);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод значения, близкого к максимально возможному числу INT64
START_TEST(pos_18)
{
    int buf_size = 21;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, INT64_MAX - 1);
    int printed_my = my_snprintf(buf, buf_size, fmt, INT64_MAX - 1);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод значения 0
START_TEST(pos_19)
{
    int buf_size = 16;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, 0);
    int printed_my = my_snprintf(buf, buf_size, fmt, 0);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод значения -1
START_TEST(pos_20)
{
    int buf_size = 16;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, -1);
    int printed_my = my_snprintf(buf, buf_size, fmt, -1);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод значения 1
START_TEST(pos_21)
{
    int buf_size = 16;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, 1);
    int printed_my = my_snprintf(buf, buf_size, fmt, 1);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод строки и максимально возможного числа INT64
START_TEST(pos_22)
{
    int buf_size = 5 + 21;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "test %lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, INT64_MAX);
    int printed_my = my_snprintf(buf, buf_size, fmt, INT64_MAX);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод максимально возможного числа INT64, а затем строки
START_TEST(pos_23)
{
    int buf_size = 5 + 21;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld test";

    int printed_target = snprintf(target_buf, buf_size, fmt, INT64_MAX);
    int printed_my = my_snprintf(buf, buf_size, fmt, INT64_MAX);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод строки и минимально возможного числа INT64
START_TEST(pos_24)
{
    int buf_size = 5 + 21;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "test %lld";

    int printed_target = snprintf(target_buf, buf_size, fmt, INT64_MIN);
    int printed_my = my_snprintf(buf, buf_size, fmt, INT64_MIN);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод минимально возможного числа INT64, а затем строки
START_TEST(pos_25)
{
    int buf_size = 5 + 21;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%lld test";

    int printed_target = snprintf(target_buf, buf_size, fmt, INT64_MIN);
    int printed_my = my_snprintf(buf, buf_size, fmt, INT64_MIN);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}

END_TEST

// Вывод символа "процент"
START_TEST(pos_26)
{
    int buf_size = 22;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%%";

    int printed_target = snprintf(target_buf, buf_size, "%s", fmt);
    int printed_my = my_snprintf(buf, buf_size, fmt);

    //printf("|%s|%s|\n", buf, target_buf);
    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод символа "процент", а затем строки
START_TEST(pos_27)
{
    int buf_size = 22;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%% %s";

    int printed_target = snprintf(target_buf, buf_size, fmt, "123");
    int printed_my = my_snprintf(buf, buf_size, fmt, "123");

    //printf("|%s|%s|\n", buf, target_buf);
    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод символа "процент" в качестве строки (используя спецификатор %s) (размер буфера 1)
START_TEST(pos_28)
{
    int buf_size = 1;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%s";

    int printed_target = snprintf(target_buf, buf_size, fmt, "%");
    int printed_my = my_snprintf(buf, buf_size, fmt, "%");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// Вывод символа "процент" в качестве строки (используя спецификатор %s) (размер буфера 2)
START_TEST(pos_29)
{
    int buf_size = 2;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "%s";

    int printed_target = snprintf(target_buf, buf_size, fmt, "%");
    int printed_my = my_snprintf(buf, buf_size, fmt, "%");

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);
}
END_TEST

// // Ловушка в качестве ложного спецификатора %s
// START_TEST(pos_30)
// {
//     int buf_size = 15;
//     char buf[buf_size];
//     char target_buf[buf_size];
//     char *fmt = "%%%% %%a";

//     int printed_target = snprintf(target_buf, buf_size, "%s", fmt);
//     int printed_my = my_snprintf(buf, buf_size, fmt);

//     printf("|%s|%s|\n", buf, target_buf);
//     ck_assert_int_eq(printed_target, printed_my);
//     ck_assert_str_eq(buf, target_buf);

// }
// END_TEST

// Пустая строка %s
START_TEST(pos_31)
{
    int buf_size = 5;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "";

    int printed_target = snprintf(target_buf, buf_size, "%s", fmt);
    int printed_my = my_snprintf(buf, buf_size, fmt);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);

}
END_TEST

// Незаконченный спецификатор
START_TEST(pos_32)
{
    int buf_size = 5;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = "asdasd %";

    int printed_target = snprintf(target_buf, buf_size, "%s", fmt);
    int printed_my = my_snprintf(buf, buf_size, fmt);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);

}
END_TEST

// NULL-строка форматирования
START_TEST(pos_33)
{
    int buf_size = 5;
    char buf[buf_size];
    char target_buf[buf_size];
    char *fmt = NULL;

    int printed_target = snprintf(target_buf, buf_size, "%s", fmt);
    int printed_my = my_snprintf(buf, buf_size, fmt);

    ck_assert_int_eq(printed_target, printed_my);
    ck_assert_str_eq(buf, target_buf);

}
END_TEST

// NULL-буфер
START_TEST(pos_34)
{
    int buf_size = 1;
    char *buf = NULL;
    char *fmt = "1234";

    int printed_target = 4;
    int printed_my = my_snprintf(buf, buf_size, fmt);

    ck_assert_int_eq(printed_target, printed_my);
}
END_TEST

// буфер имеет размер 0
START_TEST(pos_35)
{
    int buf_size = 0;
    char *buf = NULL;
    char *fmt = "1234";

    int printed_target = 4;
    int printed_my = my_snprintf(buf, buf_size, fmt);

    ck_assert_int_eq(printed_target, printed_my);
}
END_TEST

Suite *printf_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("snprintf suite");
    tc_core = tcase_create("snprintf");

    tcase_add_test(tc_core, pos_1);
    tcase_add_test(tc_core, pos_2);
    tcase_add_test(tc_core, pos_3);
    tcase_add_test(tc_core, pos_4);
    tcase_add_test(tc_core, pos_5);
    tcase_add_test(tc_core, pos_6);
    tcase_add_test(tc_core, pos_7);
    tcase_add_test(tc_core, pos_8);
    tcase_add_test(tc_core, pos_9);
    tcase_add_test(tc_core, pos_10);
    tcase_add_test(tc_core, pos_11);
    tcase_add_test(tc_core, pos_12);
    tcase_add_test(tc_core, pos_13);
    tcase_add_test(tc_core, pos_14);
    tcase_add_test(tc_core, pos_15);
    tcase_add_test(tc_core, pos_16);
    tcase_add_test(tc_core, pos_17);
    tcase_add_test(tc_core, pos_18);
    tcase_add_test(tc_core, pos_19);
    tcase_add_test(tc_core, pos_20);
    tcase_add_test(tc_core, pos_21);
    tcase_add_test(tc_core, pos_22);
    tcase_add_test(tc_core, pos_23);
    tcase_add_test(tc_core, pos_24);
    tcase_add_test(tc_core, pos_25);
    tcase_add_test(tc_core, pos_26);
    tcase_add_test(tc_core, pos_27);
    tcase_add_test(tc_core, pos_28);
    tcase_add_test(tc_core, pos_29);
    // tcase_add_test(tc_core, pos_30);
    tcase_add_test(tc_core, pos_31);
    tcase_add_test(tc_core, pos_32);
    tcase_add_test(tc_core, pos_33);
    tcase_add_test(tc_core, pos_34);
    tcase_add_test(tc_core, pos_35);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int number_failed = 0;
    SRunner *sr;
    sr = srunner_create(printf_suite());
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed != 0);
}
