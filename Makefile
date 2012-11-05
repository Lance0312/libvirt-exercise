CC = gcc
SRC_DIR = src
SRC = $(notdir $(wildcard $(SRC_DIR)/*.c))
BUILD_DIR = build
BUILD_TARGET = $(patsubst %.c, $(BUILD_DIR)/%, $(SRC))
LIBS = -lvirt


$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	$(cc-command)

all: $(BUILD_TARGET)

$(BUILD_TARGET): | $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir $@

.PHONY : clean
clean:
	@rm -rf $(BUILD_DIR)

define cc-command =
$(CC) $< -o $@ $(LIBS)
endef
