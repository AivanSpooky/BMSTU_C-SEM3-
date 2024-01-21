CC := gcc
CFLAGS := --std=c99 -Wall -Werror -Wpedantic -g -O0

TARGET := app.exe

$(TARGET): main.o node.o node_list.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c err_codes.h node_list.h
	$(CC) $(CFLAGS) -o $@ -c $<

node_list.o: node_list.c node_list.h node.h
	$(CC) $(CFLAGS) -o $@ -c $<

node.o: node.c node.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f ./*.o
	rm -f ./*.exe

.PHONY: clean_txt
clean_txt:
	rm -f ./*.txt