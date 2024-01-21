INCDIR := ../lab_10_03_common
SRCDIR := ./
OUTDIR := ./
UNITDIR := ../lab_10_03_common

vpath %.c $(SRCDIR) $(UNITDIR)

CC := gcc
CFLAGS := -std=c99 -I $(INCDIR) -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion
LDFLAGS := -lm
#UNFLAGS := -I -L -lcheck -lpthread -lrt -lsubunit -lm
UNFLAGS := -I -L -lcheck -lpthread -lrt -lm

SRCS := $(wildcard $(SRCDIR)/*.c)  # список файлов .c из src
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)  # список файлов .o из src

TEST_SRCS := $(wildcard $(UNITDIR)/*.c)
ALL_OBJS := $(OBJS) $(TEST_SRCS:$(UNITDIR)/%.c=$(OUTDIR)/%.o)
DEPS := $(ALL_OBJS:.o=.d)
TEST_OBJS := $(filter-out $(OUTDIR)/main.o, $(ALL_OBJS))

.PHONY: unit
unit: unit_tests.exe
unit:
	./unit_tests.exe

.PHONY: unit_val
unit_val: CFLAGS += -O0 -g
unit_val: UNFLAGS += -lsubunit
unit_val: unit_tests.exe
unit_val:
	valgrind --leak-check=yes -q ./unit_tests.exe

unit_tests.exe: $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(UNFLAGS)

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUTDIR)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -M $< > $@

-include $(DEPS)

.PHONY: clean
clean: 
	rm -f ./*.d ./*.exe ./*.txt ./*.o