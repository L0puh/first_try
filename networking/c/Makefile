CC=gcc
SOURCES=$(wildcard *.c)
BUILD_DIR=build
RUN_DIR=run

all: $(patsubst %.c, $(RUN_DIR)/%, $(SOURCES))

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< -Iinclude

$(RUN_DIR)/%: $(BUILD_DIR)/%.o
	mkdir -p $(RUN_DIR)
	$(CC) -o $@ $< -Iinclude

clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(RUN_DIR)/*
