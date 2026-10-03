CC       = gcc
CPPFLAGS = -Icompalg -MMD -MP
CFLAGS   = -std=c89 -Wall -Wextra -pedantic -g -O2
LDLIBS   = -lm

BUILD = build

# library sources shared by the assignments (src/timing.c has its own main)
LIB_SRCS = src/nt.c src/rational.c src/la.c src/real.c src/format.c
LIB_OBJS = $(LIB_SRCS:src/%.c=$(BUILD)/%.o)

# each assignment1/problemN.c has its own main and becomes build/assignment1/problemN
A1_SRCS = $(wildcard assignment1/problem*.c)
A1_OBJS = $(A1_SRCS:%.c=$(BUILD)/%.o)
A1_BINS = $(A1_OBJS:.o=)

.PHONY: all assignment1 run clean

all: assignment1

assignment1: $(A1_BINS)

$(A1_BINS): %: %.o $(LIB_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(A1_OBJS): $(BUILD)/%.o: %.c | $(BUILD)/assignment1
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BUILD) $(BUILD)/assignment1:
	mkdir -p $@

# make run-problem9 builds and runs just that problem
run-%: $(BUILD)/assignment1/%
	./$<

run: assignment1
	for p in $(A1_BINS); do echo "== $$p"; ./$$p || exit 1; done

clean:
	rm -rf $(BUILD)

-include $(LIB_OBJS:.o=.d) $(A1_OBJS:.o=.d)
