INCDIR := ./inc
INC := -I inc/
SRCDIR := ./src
OUTDIR := ./out
UNITDIR := ./unit_tests

vpath %.c $(SRCDIR) $(UNITDIR)

CC := gcc
CLANG := clang
CFLAGS := -std=c99 -I $(INCDIR) -Werror -Wall -Wextra -Wfloat-equal -Wfloat-conversion
LDFLAGS := -lm
UNFLAGS := -I -L -lcheck -lpthread -lrt -lsubunit -lm
# UNFLAGS := -I -L -lcheck -lpthread -lrt -lm

SRCS := $(wildcard $(SRCDIR)/*.c)  # список файлов .c из src
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)  # список файлов .o из src

TEST_SRCS := $(wildcard $(UNITDIR)/*.c)
ALL_OBJS := $(OBJS) $(TEST_SRCS:$(UNITDIR)/%.c=$(OUTDIR)/%.o)
DEPS := $(ALL_OBJS:.o=.d)
TEST_OBJS := $(filter-out $(OUTDIR)/main.o, $(ALL_OBJS))

.PHONY: release
release: array.so

.PHONY: unit
unit: array.so
unit: unit_tests.exe
unit:
	./unit_tests.exe

.PHONY: unit_val
unit_val: UNFLAGS += -lsubunit
unit_val: CFLAGS += -O0 -g
unit_val: array.so
unit_val: unit_tests.exe
unit_val: 
	valgrind --leak-check=yes -q ./unit_tests.exe

unit_tests.exe: $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(UNFLAGS) -Wl,-rpath=$(OUTDIR)

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUTDIR)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -M $< > $@

-include $(DEPS)

# .PHONY: compile_dynamic_with_flags

array.so: $(SRCDIR)/array.c $(INCDIR)/array.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

.PHONY: clean
clean:
	rm -f ./out/*.o
	rm -f ./out/*.a
	rm -f ./*.so
	rm -fr $(OUTDIR)
	rm -fr ../python/__pycache__
	rm -f ./**/*.exe
	rm -f ./*.exe