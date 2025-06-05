 CC = gcc
CFLAGS = -Wall -Icontroller
BUILD_DIR = build

# Fontes
MAIN_SRC = main.c
VIEW_SRCS = $(wildcard view/*.c)
CONTROLLER_SRCS = $(wildcard controller/*.c)
SRCS = $(MAIN_SRC) $(VIEW_SRCS) $(CONTROLLER_SRCS)

# Objetos
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

# Alvo final
TARGET = programa

all: $(BUILD_DIR) $(TARGET)

# Cria diretório build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra para compilar todos os .o
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: view/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: controller/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Linkagem final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -mconsole -o $@ $^

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
