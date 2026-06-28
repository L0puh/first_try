BUILD_DIR = build
SRCS = $(wildcard *.s)
OBJS = $(SRCS:%.s=$(BUILD_DIR)/%.o)
PROG = $(OBJS:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.out)

AS = as
LD = ld

all: ${PROG}

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	${AS} -c -o $@ $<

${PROG}: ${OBJS}
	${LD} -o $@ ${OBJS}

clean:
	rm -rf $(BUILD_DIR)
