CC = clang
CFLAGS = -xc -std=c17 -Iinclude -Wall -Wpedantic -Wextra

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -O0 -g
else
	CFLAGS += -Oz -flto
endif

ifeq ($(OS), Windows_NT)
	RMTARGET := if exist target rmdir /s/q target
	MKTARGET := if not exist target mkdir target
	EXEC := target\Main.exe
else
	RMTARGET := rmdir -rf target
	MKTARGET := mkdir -p target
	EXEC := target/Main
endif

all: $(EXEC)

.PHONY: clean
clean:
	$(RMTARGET)

$(EXEC): target/Main.o
	@$(MKTARGET)
	$(CC) target/Main.o -o $(EXEC) $(CFLAGS)

target/%.o: src/%.c
	@$(MKTARGET)
	$(CC) -c $< -o $@ $(CFLAGS)

target/Stack.o: target/Object.o
