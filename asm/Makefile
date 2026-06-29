BUILD_DIR = build
SRCS = $(wildcard *.s)
OBJS = $(SRCS:%.s=$(BUILD_DIR)/%.o)
PROGS = $(SRCS:%.s=$(BUILD_DIR)/%.out)

AS = as
LD = ld
ASFLAGS = -g --32
LDFLAGS = -m elf_i386

all: ${PROGS}

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	${AS} ${ASFLAGS} -c -o $@ $<

$(BUILD_DIR)/%.out: $(BUILD_DIR)/%.o
	${LD} ${LDFLAGS} -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
