CC = gcc
CFLAGS = -Wall -Icontroller
BUILD_DIR = build

# Fontes
MAIN_SRC = main.c
VIEW_SRCS = $(wildcard view/*.c)
CONTROLLER_SRCS = $(wildcard controller/*.c)
SRCS = $(MAIN_SRC) $(VIEW_SRCS) $(CONTROLLER_SRCS)

# Objetos (mantém os caminhos corretos dos .c)
OBJS = $(SRCS:.c=.o)
OBJS_BUILD = $(patsubst %.o,$(BUILD_DIR)/%.o,$(OBJS))

# Alvo final
TARGET = programa

all: $(BUILD_DIR) $(TARGET)

# Cria diretório build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/view $(BUILD_DIR)/controller

# Compilação dos .c para .o no diretório build/
$(BUILD_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/view/%.o: view/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/controller/%.o: controller/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Linkagem final
$(TARGET): $(BUILD_DIR)/main.o $(patsubst view/%.c,$(BUILD_DIR)/view/%.o,$(VIEW_SRCS)) $(patsubst controller/%.c,$(BUILD_DIR)/controller/%.o,$(CONTROLLER_SRCS))
	$(CC) $(CFLAGS) -mconsole -o $@ $^

# Limpeza
clean:
	rm -rf $(BUILD_DIR) programa
