CC := gcc
CFLAGS := --std=c99 -Wall -Wpedantic -Werror -g -O0
CFLAGS_NO_PEDANTIC := --std=c99 -Wall -Werror -g -O0

TARGET := app.exe
TEST := test.exe

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $@ $^

$(TEST): test.o
	$(CC) $(CFLAGS) -o $@ $^

test.o: test_01.c
	$(CC) $(CFLAGS) -o $@ -c $<

main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY clean:
	rm -f $(TARGET) ./*.o
