#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR 1

// Функции динамического выделения памяти
#if OK == ERR
Утилита make: назначение, переменные, шаблонные правила
make — утилита, автоматизирующая процесс преобразования файлов из одной формы в другую. Необходимо создать так называемый сценарий сборки проекта (make-файл).
Этот файл описывает
• отношения между файлами программы;
• содержит команды для обновления каждого файла.
Утилита make использует информацию из make-файла и время последнего изменения каждого файла для того, чтобы решить, какие файлы нужно обновить.

Разновидности утилиты make.
• GNU Make (рассматривается на курсе)
• BSD Make
• Microsoft Make (nmake)

• Сценарий сборки проекта: название файла, структура сценария сборки
цель: зависимость_1 ... зависимость_n
[tab]команда_1
[tab]команда_2
...
[tab]команда_m

что создать/сделать: из чего создать
как создать/что сделать

Утилита make руководствуется правилами, описанными в файле Makefile. Эти правила состоят из следующих составных частей:
Цели (Targets): Цель представляет собой файл или действие, которое нужно выполнить.
Зависимости (Dependencies): Зависимости представляют собой файлы или другие цели, от которых зависит текущая цель.
Команды сборки (Build Commands): Это команды, которые нужно выполнить для сборки цели.

Особенности выполнения команд
• Ненулевой код возврата может прервать выполнение сценария.
• Каждая команда выполняется в своём shell.

Использование переменных. Примеры использования.
Определить переменную в make-файле можно следующим образом:
CC := gcc
Чтобы получить значение переменной, необходимо её имя заключить в круглые скобки и перед ними поставить символ '$'.
$(CC)

# Компилятор
CC := gcc
# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror -pedantic
# Общие объектные файлы
OBJS := hello.o bye.o
ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif
ifeq ($(mode), release)
    # утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

greeting.exe: $(OBJS) main.o
    $(CC) $^ -o $@
test_greeting.exe: $(OBJS) test.o
    $(CC) $^ -o $@
%.o: %.c *.h
    $(CC) $(CFLAGS) -c $<
.PHONY: clean
clean:
    $(RM) *.o *.exe

Переменные, зависящие от цели. Примеры использования.
К предыдущему вопросу
debug: CFLAGS += -g3
debug: greeting.exe

release: CFLAGS += -DNDEBUG -g0
release: greeting.exe

1 - Ручной анализ зависимостей
app: main.o utils.o
    gcc -o app main.o utils.o

main.o: main.c utils.h
    gcc -c main.c

utils.o: utils.c utils.h
    gcc -c utils.c

2 - Автоматический анализ зависимостей
CC = gcc
CFLAGS = -MMD -MP

app: main.o utils.o
    $(CC) -o app main.o utils.o

-include $(wildcard *.d)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@
3 - Любой файл С зависит от файла H
CC = gcc
CFLAGS = -MMD -MP

app: main.o utils.o
    $(CC) -o app main.o utils.o

-include $(wildcard *.d)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

%.o: %.h
    @echo "Header file changed: $<"

#endif

#ifdef OK // Функции

#endif


int main(void)
{
    return OK;
}