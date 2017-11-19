CC := gcc
CFLAGS += -std=c11 -Wall -O2
LDFLAGS += -s
LIBS := -lws2_32

BIN := server.exe client.exe

.PHONY: all
all: $(BIN)

.PHONY: clean
clean:
	$(RM) -f $(BIN) *.o

# 这个目标的依赖只是“凑巧”
%.exe: %.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c Makefile
	$(CC) -c -o $@ $(CFLAGS) $<
