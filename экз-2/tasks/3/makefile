CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -g -O0

TARGET := app.exe

$(TARGET): main.o node_list.o node.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c node_list.h
	$(CC) $(CFLAGS) -o $@ -c $<

node_list.o: node_list.c node_list.h node.h
	$(CC) $(CFLAGS) -o $@ -c $<

node.o: node.c node.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY clean:
	rm -f $(TARGET) ./*.o