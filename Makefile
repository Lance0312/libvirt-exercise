CC = gcc
SRC_DIR = src
BUILD_DIR = build
LIBS=-lvirt

all: $(patsubst %.c, %, $(wildcard $(SRC_DIR)/*.c))

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	$(cc-command)

build:
	@mkdir $@

.PHONY : clean
clean:
	@rm -rf $(BUILD_DIR)

define cc-command =
$(CC) $< -o $@ $(LIBS)
endef
