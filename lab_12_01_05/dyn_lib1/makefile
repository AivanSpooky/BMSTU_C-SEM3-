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
TEST_OBJS := $(TEST_SRCS:$(UNITDIR)/%.c=$(OUTDIR)/%.o)
ALL_OBJS := $(OBJS) $(TEST_OBJS)
DEPS := $(ALL_OBJS:.o=.d)

.PHONY: release
release: compile_dynamic_with_flags

.PHONY: debug
debug: CFLAGS += -O0 -g
debug: compile_dynamic_with_flags
debug: app.exe

.PHONY: func
func: compile_dynamic_with_flags
func:
	./func_tests/scripts/func_tests.sh 0

.PHONY: func_val
func_val: compile_dynamic_with_flags
func_val:
	./func_tests/scripts/func_tests.sh 1

.PHONY: collect_coverage
collect_coverage:
	cd out && gcov -o ./ ../$(SRCDIR)/*.c

.PHONY: unit
unit: compile_unit_tests
unit:
	./unit_tests.exe

.PHONY: unit_val
unit_val: UNFLAGS += -lsubunit
unit_val: CFLAGS += -O0 -g
unit_val: compile_unit_tests
unit_val: 
	valgrind --leak-check=yes -q ./unit_tests.exe

.PHONY: all
all: sanitize_check
all: unit

app.exe: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

compile_unit_tests: $(TEST_OBJS) $(OUTDIR)/dyn_lib.so
	$(CC) $(CFLAGS) $^ -o unit_tests.exe $(UNFLAGS) -L $(OUTDIR)/dyn_lib.so $(LDFLAGS)

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUTDIR)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -M $< > $@

-include $(DEPS)

.PHONY: compile_static
compile_static: $(OUTDIR)/main.o $(OUTDIR)/stat_lib.a
	$(CC) -o app.exe $^ -L $(OUTDIR)/ 

compile_dynamic_with_flags: $(OUTDIR)/main.o $(OUTDIR)/dyn_lib.so
	$(CC) -o app.exe $^ -L $(OUTDIR)/ 

compile_dynamic_with_h_file: $(OUTDIR)/main.o $(OUTDIR)/dyn_lib.so
	$(CLANG) -o app.exe $^ -ldl -L$(OUTDIR) 

$(OUTDIR)/stat_lib.a: $(OUTDIR)/file_op.o $(OUTDIR)/funcs.o
	ar cr $(OUTDIR)/stat_lib.a $(OUTDIR)/file_op.o $(OUTDIR)/funcs.o
	ranlib $(OUTDIR)/stat_lib.a

$(OUTDIR)/dyn_lib.so: $(SRCDIR)/file_op.c $(SRCDIR)/funcs.c $(INCDIR)/file_op.h $(INCDIR)/funcs.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

.PHONY: clean
clean:
	rm -f ./out/*.o
	rm -f ./out/*.a
	rm -f ./out/*.so
	rm -fr $(OUTDIR)
	rm -f ./**/*.exe
	rm -f ./*.exe
